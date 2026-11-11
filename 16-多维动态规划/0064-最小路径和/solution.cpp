/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n);                          // dp[j]：走到当前这一行第 j 格的最小路径和
        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) dp[j] = dp[j - 1] + grid[0][j];   // 第一行只能从左边来
        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0];                    // 第一列只能从上面来
            for (int j = 1; j < n; ++j)
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];   // 上面（旧 dp[j]）、左边取小的
        }
        return dp[n - 1];
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}
static void printVecs(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ",";
        printVec(v[i]);
    }
    cout << "]";
}

int main() {
    struct Case {
        vector<vector<int>> grid;
        int expected;
    };
    vector<Case> cases = {
        {{{1, 3, 1}, {1, 5, 1}, {4, 2, 1}}, 7},
        {{{1, 2, 3}, {4, 5, 6}}, 12},
        {{{5}}, 5},
        {{{1, 2, 3, 4}}, 10},
        {{{1}, {2}, {3}}, 6},
        {{{1, 9, 1, 1}, {1, 9, 1, 9}, {1, 1, 1, 1}}, 6},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.minPathSum(c.grid);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": grid = ";
        printVecs(c.grid);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
