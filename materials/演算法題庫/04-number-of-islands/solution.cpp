#include <array>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;

        const int rows = static_cast<int>(grid.size());
        const int cols = static_cast<int>(grid[0].size());
        constexpr array<pair<int, int>, 4> directions{{
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        }};
        int islands = 0;

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] != '1') continue;

                ++islands;
                grid[row][col] = '0';
                stack<pair<int, int>> pending;
                pending.push({row, col});

                while (!pending.empty()) {
                    const auto [currentRow, currentCol] = pending.top();
                    pending.pop();

                    for (const auto [dr, dc] : directions) {
                        const int nextRow = currentRow + dr;
                        const int nextCol = currentCol + dc;
                        if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols) {
                            continue;
                        }
                        if (grid[nextRow][nextCol] != '1') continue;

                        grid[nextRow][nextCol] = '0';
                        pending.push({nextRow, nextCol});
                    }
                }
            }
        }

        return islands;
    }
};
