#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <cctype>

using namespace std;

unordered_map<string, char> segmentToChar;
unordered_map<char, string> charToSegment;

void setupSegmentMaps() {
    segmentToChar[" _ | ||_|"] = '0';
    segmentToChar["     |  |"] = '1';
    segmentToChar[" _  _||_ "] = '2';
    segmentToChar[" _  _ |_|"] = '3';
    segmentToChar["   |_|  |"] = '4';
    segmentToChar[" _ |_  _|"] = '5';
    segmentToChar[" _ |_ |_|"] = '6';
    segmentToChar[" _   |  |"] = '7';
    segmentToChar[" _ |_||_|"] = '8';
    segmentToChar[" _ |_| _|"] = '9';
    segmentToChar["   | |   "] = '+';
    segmentToChar["  _      "] = '-';
    segmentToChar["_ _  _|_|_"] = '*';
    segmentToChar[" _ |_| _|"] = '/';
    segmentToChar["  _   _  "] = '=';

    for(auto const& pair : segmentToChar) {
        charToSegment[pair.second] = pair.first;
    }
}

long long evaluateEquation(const vector<char>& equation) {
    long long lhs = 0;
    long long currentNum = 0;
    char op = '+';

    for (char c : equation) {
        if (isdigit(c)) {
            currentNum = currentNum * 10 + (c - '0');
        } else {
            if (op == '+') lhs += currentNum;
            else if (op == '-') lhs -= currentNum;
            else if (op == '*') lhs *= currentNum;
            else if (op == '/') lhs /= currentNum;
            
            op = c;
            currentNum = 0;
        }
    }

    if (op == '+') lhs += currentNum;
    else if (op == '-') lhs -= currentNum;
    else if (op == '*') lhs *= currentNum;
    else if (op == '/') lhs /= currentNum;

    return lhs;
}

int countDiff(const string& s1, const string& s2) {
    int diff = 0;
    for (size_t i = 0; i < s1.length(); ++i) {
        if (s1[i] != s2[i]) {
            diff++;
        }
    }
    return diff;
}

int main() {
    setupSegmentMaps();
    int N;
    cin >> N;
    cin.ignore();

    vector<string> inputRows(3);
    for (int i = 0; i < 3; ++i) {
        string temp;
        getline(cin, temp);
        for(char c : temp) {
            if (c != ' ' && c != '\n' && c != '\r') {
                inputRows[i] += c;
            }
        }
    }

    vector<string> chars(N);
    for(int i = 0; i < N; ++i) {
        string s = "";
        for(int j = 0; j < 3; ++j) {
            s += inputRows[j].substr(i * 3, 3);
        }
        chars[i] = s;
    }
    
    int equalsPos = -1;
    for(int i = 0; i < N; ++i) {
        if (segmentToChar.count(chars[i]) && segmentToChar.at(chars[i]) == '=') {
            equalsPos = i;
            break;
        }
    }

    long long rhs = 0;
    if (equalsPos != -1) {
        long long multiplier = 1;
        for (int i = N - 1; i > equalsPos; --i) {
            rhs += (long long)(segmentToChar.at(chars[i]) - '0') * multiplier;
            multiplier *= 10;
        }
    }

    for (int i = 0; i < equalsPos; ++i) {
        for (auto const& pair : segmentToChar) {
            string correctSegment = pair.first;
            char correctChar = pair.second;
            
            if (countDiff(chars[i], correctSegment) == 1) {
                vector<char> equation;
                for(int j = 0; j < equalsPos; ++j) {
                    if (j == i) {
                        equation.push_back(correctChar);
                    } else {
                        equation.push_back(segmentToChar.at(chars[j]));
                    }
                }
                
                if (evaluateEquation(equation) == rhs) {
                    cout << i + 1 << endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}