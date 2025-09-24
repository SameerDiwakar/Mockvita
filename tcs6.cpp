#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <iomanip>
#include <functional>

using namespace std;

int N;
vector<string> grid;

struct Point {
    int r, c;
};

bool isValid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

double solve() {
    int start_r = -1, start_c = -1;
    int end_r = -1, end_c = -1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == '.' && (i == 0 || i == N - 1 || j == 0 || j == N - 1)) {
                if (start_r == -1) {
                    start_r = i;
                    start_c = j;
                } else {
                    end_r = i;
                    end_c = j;
                }
            }
        }
    }

    function<pair<bool, double>(int, int, int, int)> findResistance = 
        [&](int r, int c, int pr, int pc) -> pair<bool, double> {
        if (r == end_r && c == end_c) return {true, 0.0};

        vector<pair<int, int>> next_points;
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (!isValid(nr, nc) || (nr == pr && nc == pc)) continue;

            if ((grid[r][c] == '|' && (dr[i] == 1 || dr[i] == -1)) ||
                (grid[r][c] == '-' && (dc[i] == 1 || dc[i] == -1)) ||
                 grid[r][c] == '+' || grid[r][c] == '.') {
                next_points.push_back({nr, nc});
            }
        }

        if (next_points.empty()) return {false, 0.0};

        if (next_points.size() == 1) {
            auto [found, res] = findResistance(next_points[0].first, next_points[0].second, r, c);
            if (found) {
                return {true, res + (grid[next_points[0].first][next_points[0].second] != '.' ? 1.0 : 0.0)};
            }
        } else {
            double total_parallel_res = 0.0;
            bool found_path = false;
            
            for (const auto& next_p : next_points) {
                auto [found, res] = findResistance(next_p.first, next_p.second, r, c);
                if (found) {
                    found_path = true;
                    total_parallel_res += 1.0 / res;
                }
            }
            if (found_path) return {true, 1.0 / total_parallel_res};
        }
        return {false, 0.0};
    };

    auto [found, result] = findResistance(start_r, start_c, -1, -1);
    
    int first_resistor_r = start_r, first_resistor_c = start_c;
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    for (int i = 0; i < 4; ++i) {
        int nr = start_r + dr[i];
        int nc = start_c + dc[i];
        if (isValid(nr, nc)) {
            first_resistor_r = nr;
            first_resistor_c = nc;
            break;
        }
    }
    
    return result + (grid[first_resistor_r][first_resistor_c] != '.' ? 1.0 : 0.0);
}

int main() {
    cin >> N;
    grid.resize(N);
    for (int i = 0; i < N; ++i) cin >> grid[i];
    cout << fixed << setprecision(1) << solve();
    return 0;
}