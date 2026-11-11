/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[j]：走到当前这一行第 j 格有几种走法（只留一行，一行一行往下滚）
        vector<int> dp(n, 1);                       // 第一行：只能一直往右，每格都是 1 种
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                dp[j] += dp[j - 1];                 // 从上面来（旧 dp[j]）+ 从左边来（dp[j-1]）
        return dp[n - 1];
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        int m, n, expected;
    };
    vector<Case> cases = {
        {3, 7, 28},
        {3, 2, 3},
        {7, 3, 28},
        {3, 3, 6},
        {1, 1, 1},
        {1, 5, 1},
        {10, 10, 48620},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.uniquePaths(c.m, c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": m = " << c.m << ", n = " << c.n;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
