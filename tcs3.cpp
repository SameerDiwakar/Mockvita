#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <set>

using namespace std;

int M, N;
vector<string> grid;

int dx[] = {-1, 0, 1, 0}; 
int dy[] = {0, 1, 0, -1};

int getNewDirection(char mirror, int direction) {
    if (mirror == '/') {
        if (direction == 0) return 3;
        if (direction == 1) return 2;
        if (direction == 2) return 1;
        if (direction == 3) return 0;
    } else if (mirror == '\\') {
        if (direction == 0) return 1;
        if (direction == 1) return 0;
        if (direction == 2) return 3;
        if (direction == 3) return 2;
    }
    return -1;
}

int solve() {
    int max_cells = 0;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == '/' || grid[i][j] == '\\') {
                for (int start_dir = 0; start_dir < 4; ++start_dir) {
                    int current_x = i;
                    int current_y = j;
                    int current_dir = start_dir;
                    set<pair<int, int>> visited_cells;
                    set<tuple<int, int, int>> visited_states;

                    bool loop_found = false;
                    while (true) {
                        if (visited_states.count({current_x, current_y, current_dir})) {
                            loop_found = true;
                            break;
                        }
                        visited_states.insert({current_x, current_y, current_dir});

                        current_dir = getNewDirection(grid[current_x][current_y], current_dir);
                        
                        current_x += dx[current_dir];
                        current_y += dy[current_dir];

                        if (current_x < 0 || current_x >= M || current_y < 0 || current_y >= N) {
                            break;
                        }

                        visited_cells.insert({current_x, current_y});

                        if (grid[current_x][current_y] != '/' && grid[current_x][current_y] != '\\') {
                            continue;
                        }
                    }

                    if (loop_found) {
                        max_cells = max(max_cells, (int)visited_cells.size());
                    }
                }
            }
        }
    }
    return max_cells;
}

int main() {
    cin >> M >> N;
    grid.resize(M);
    for (int i = 0; i < M; ++i) {
        grid[i].resize(N);
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    cout << solve() << endl;

    return 0;
}