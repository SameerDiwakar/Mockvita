#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <map>
#include <tuple>
#include <set>
#include <algorithm>

using namespace std;

struct Line {
    int x1, y1, x2, y2;
};

double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

bool isCollinear(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1);
}

bool onSegment(int x1, int y1, int x2, int y2, int x, int y) {
    return (x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1, y2));
}

pair<double, double> getIntersection(const Line& l1, const Line& l2) {
    long long a1 = l1.y2 - l1.y1;
    long long b1 = l1.x1 - l1.x2;
    long long c1 = a1 * l1.x1 + b1 * l1.y1;

    long long a2 = l2.y2 - l2.y1;
    long long b2 = l2.x1 - l2.x2;
    long long c2 = a2 * l2.x1 + b2 * l2.y2;

    long long determinant = a1 * b2 - a2 * b1;
    if (determinant == 0) {
        return {numeric_limits<double>::max(), numeric_limits<double>::max()};
    }

    double x = (double)(b2 * c1 - b1 * c2) / determinant;
    double y = (double)(a1 * c2 - a2 * c1) / determinant;
    
    if (onSegment(l1.x1, l1.y1, l1.x2, l1.y2, round(x), round(y)) &&
        onSegment(l2.x1, l2.y1, l2.x2, l2.y2, round(x), round(y))) {
        return {x, y};
    }
    return {numeric_limits<double>::max(), numeric_limits<double>::max()};
}

int main() {
    int N;
    cin >> N;
    vector<Line> lines(N);
    for (int i = 0; i < N; ++i) {
        cin >> lines[i].x1 >> lines[i].y1 >> lines[i].x2 >> lines[i].y2;
    }
    int K;
    cin >> K;

    map<pair<int, int>, vector<int>> intersections;
    
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (isCollinear(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2, lines[j].x1, lines[j].y1) ||
                isCollinear(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2, lines[j].x2, lines[j].y2)) {
                continue;
            }
            
            pair<double, double> intersect = getIntersection(lines[i], lines[j]);
            if (intersect.first != numeric_limits<double>::max() &&
                abs(intersect.first - round(intersect.first)) < 1e-9 &&
                abs(intersect.second - round(intersect.second)) < 1e-9) {
                
                int ix = round(intersect.first);
                int iy = round(intersect.second);

                intersections[{ix, iy}].push_back(i);
                intersections[{ix, iy}].push_back(j);
            }
        }
    }
    
    int totalIntensity = 0;
    for (auto& pair : intersections) {
        auto& intersectionLines = pair.second;
        sort(intersectionLines.begin(), intersectionLines.end());
        intersectionLines.erase(unique(intersectionLines.begin(), intersectionLines.end()), intersectionLines.end());

        if (intersectionLines.size() == K) {
            int currentIntensity = numeric_limits<int>::max();
            for (int lineIndex : intersectionLines) {
                const auto& line = lines[lineIndex];
                int x = pair.first.first;
                int y = pair.first.second;
                
                int dist1 = abs(x - line.x1) + abs(y - line.y1);
                int dist2 = abs(x - line.x2) + abs(y - line.y2);
                
                currentIntensity = min(currentIntensity, min(dist1, dist2));
            }
            totalIntensity += currentIntensity;
        }
    }

    cout << totalIntensity;
    return 0;
}