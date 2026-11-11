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
    int numSquares(int n) {
        // dp[i] = 和为 i 最少要几个完全平方数
        vector<int> dp(n + 1, n);                   // 最多 n 个 1，用 n 当初始的「很大」
        dp[0] = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j * j <= i; ++j)        // 最后一个数选 j²
                dp[i] = min(dp[i], dp[i - j * j] + 1);
        return dp[n];
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        int n, expected;
    };
    vector<Case> cases = {{12, 3}, {13, 2}, {1, 1}, {4, 1}, {7, 4}, {43, 3}, {10000, 1}};

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.numSquares(c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": n = " << c.n;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
