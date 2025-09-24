#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

int getMinOrbs(const string& potionName, const unordered_map<string, vector<vector<string>>>& allRecipes, unordered_map<string, int>& memo) {
    if (memo.count(potionName)) {
        return memo[potionName];
    }

    if (allRecipes.find(potionName) == allRecipes.end()) {
        return memo[potionName] = 0;
    }

    int minCost = numeric_limits<int>::max();

    for (const auto& ingredients : allRecipes.at(potionName)) {
        int currentCost = 0;
        for (const auto& ingredient : ingredients) {
            currentCost += getMinOrbs(ingredient, allRecipes, memo);
        }
        
        currentCost += ingredients.size() - 1;

        minCost = min(minCost, currentCost);
    }

    return memo[potionName] = minCost;
}

int main() {
    int numRecipes;
    cin >> numRecipes;
    cin.ignore(); 

    unordered_map<string, vector<vector<string>>> allRecipes;

    for (int i = 0; i < numRecipes; ++i) {
        string recipeStr;
        getline(cin, recipeStr);

        string ingredientsPart, resultPotion;
        size_t arrowPos = recipeStr.find("->");
        
        ingredientsPart = trim(recipeStr.substr(0, arrowPos));
        resultPotion = trim(recipeStr.substr(arrowPos + 2));

        stringstream ingredientsSS(ingredientsPart);
        string ingredient;
        vector<string> currentIngredients;
        
        while (getline(ingredientsSS, ingredient, '+')) {
            currentIngredients.push_back(trim(ingredient));
        }
        
        allRecipes[resultPotion].push_back(currentIngredients);
    }
    
    string targetPotion;
    getline(cin, targetPotion);
    targetPotion = trim(targetPotion);

    unordered_map<string, int> memo;

    cout << getMinOrbs(targetPotion, allRecipes, memo) << endl;

    return 0;
}