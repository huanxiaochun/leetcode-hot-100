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
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size(), side = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));   // 多一圈 0，不用判边界
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;   // 上、左、左上取最短
                    side = max(side, dp[i][j]);
                }
        return side * side;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static vector<vector<char>> grid(const vector<string>& rows) {
    vector<vector<char>> g;
    for (auto& r : rows) g.emplace_back(r.begin(), r.end());
    return g;
}

int main() {
    struct Case { vector<string> rows; int expected; };
    vector<Case> cases = {
        {{"10100", "10111", "11111", "10010"}, 4},
        {{"01", "10"}, 1},
        {{"0"}, 0},
        {{"1"}, 1},
        {{"1111", "1111", "1111"}, 9},
        {{"11", "11", "10"}, 4},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto g = grid(c.rows);
        int got = sol.maximalSquare(g);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": matrix = [";
        for (size_t t = 0; t < c.rows.size(); ++t) cout << (t ? "," : "") << c.rows[t];
        cout << "]\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
