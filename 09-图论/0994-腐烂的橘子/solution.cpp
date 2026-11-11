/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), fresh = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 2) q.push({i, j}); // 所有烂橘子一起当起点
                if (grid[i][j] == 1) ++fresh;
            }
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int minutes = 0;
        while (!q.empty() && fresh > 0) {
            ++minutes;                              // 队列里现有的这一层，都在这一分钟往外传
            for (int k = q.size(); k > 0; --k) {
                auto [i, j] = q.front();
                q.pop();
                for (auto& d : dirs) {
                    int x = i + d[0], y = j + d[1];
                    if (x < 0 || y < 0 || x >= m || y >= n || grid[x][y] != 1) continue;
                    grid[x][y] = 2;                 // 传染，下一分钟它也会往外传
                    --fresh;
                    q.push({x, y});
                }
            }
        }
        return fresh == 0 ? minutes : -1;           // 还有新鲜的：它们和烂橘子不连通
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        vector<vector<int>> grid;
        int expected;
    };
    vector<Case> cases = {
        {{{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}, 4},
        {{{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}, -1},
        {{{0, 2}}, 0},
        {{{0}}, 0},
        {{{1}}, -1},
        {{{2, 1, 1, 1, 2}}, 2},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto g = c.grid;
        int got = sol.orangesRotting(g);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": grid = [";
        for (size_t i = 0; i < c.grid.size(); ++i) {
            cout << (i ? "," : "") << "[";
            for (size_t j = 0; j < c.grid[i].size(); ++j) cout << (j ? "," : "") << c.grid[i][j];
            cout << "]";
        }
        cout << "]\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
