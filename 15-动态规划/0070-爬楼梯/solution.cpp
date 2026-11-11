/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        // dp[i] = 爬到第 i 阶的方法数 = dp[i - 1] + dp[i - 2]
        int a = 1, b = 1;                           // dp[0]、dp[1]
        for (int i = 2; i <= n; ++i) {
            int c = a + b;                          // 最后一步跨 1 阶或 2 阶
            a = b;
            b = c;                                  // 往前滚一格
        }
        return b;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        int n, expected;
    };
    vector<Case> cases = {{1, 1}, {2, 2}, {3, 3}, {5, 8}, {10, 89}, {45, 1836311903}};

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.climbStairs(c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": n = " << c.n;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
