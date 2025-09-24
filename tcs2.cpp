#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

// Using a tuple to represent a point (x, y) for map keys
using Point = pair<int, int>;

// Function to find the number of connected components
void findComponents(const Point& u, map<Point, vector<Point>>& graph, set<Point>& visited) {
    if (visited.count(u)) {
        return;
    }
    visited.insert(u);
    for (const auto& v : graph[u]) {
        findComponents(v, graph, visited);
    }
}

int main() {
    int N;
    cin >> N;

    map<Point, vector<Point>> graph;
    set<Point> uniquePoints;
    set<pair<Point, Point>> uniqueEdges;

    for (int i = 0; i < N; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Point p1 = {x1, y1};
        Point p2 = {x2, y2};

        graph[p1].push_back(p2);
        graph[p2].push_back(p1);

        uniquePoints.insert(p1);
        uniquePoints.insert(p2);

        if (p1 > p2) swap(p1, p2);
        uniqueEdges.insert({p1, p2});
    }

    int V = uniquePoints.size();
    int E = uniqueEdges.size();

    int C = 0;
    set<Point> visited;
    for (const auto& point : uniquePoints) {
        if (!visited.count(point)) {
            findComponents(point, graph, visited);
            C++;
        }
    }

    int F = E - V + C;

    cout << F; 

    return 0;
}