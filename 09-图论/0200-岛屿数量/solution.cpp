/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size(), cnt = 0;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == '1') {            // 碰到一块没淹过的陆地：新岛
                    ++cnt;
                    dfs(grid, i, j);                // 把这座岛整个淹掉，以后不会再数到
                }
        return cnt;
    }

private:
    void dfs(vector<vector<char>>& g, int i, int j) {
        int m = g.size(), n = g[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n || g[i][j] != '1') return;   // 出界或不是陆地
        g[i][j] = '0';                              // 先淹掉再往外走，防止走回来
        dfs(g, i + 1, j);
        dfs(g, i - 1, j);
        dfs(g, i, j + 1);
        dfs(g, i, j - 1);
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printGrid(const vector<vector<char>>& g) {
    cout << "[";
    for (size_t i = 0; i < g.size(); ++i) {
        cout << (i ? "," : "") << "\"";
        for (char c : g[i]) cout << c;
        cout << "\"";
    }
    cout << "]";
}

static vector<vector<char>> toGrid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& r : rows) g.emplace_back(r.begin(), r.end());
    return g;
}

int main() {
    struct Case {
        vector<string> grid;
        int expected;
    };
    vector<Case> cases = {
        {{"11110", "11010", "11000", "00000"}, 1},
        {{"11000", "11000", "00100", "00011"}, 3},
        {{"0"}, 0},
        {{"1"}, 1},
        {{"101", "010", "101"}, 5},
        {{"111", "101", "111"}, 1},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto g = toGrid(c.grid);
        cout << "用例 " << k + 1 << ": grid = ";
        printGrid(g);
        int got = sol.numIslands(g);
        bool ok = got == c.expected;
        passed += ok;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
