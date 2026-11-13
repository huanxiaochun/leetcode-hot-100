/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    long long backToOrigin(int n, int len = 10) {
        // 每步 2 种走法，答案不超过 2^n：n ≤ 60 时 long long 放得下
        // n 再大就会溢出，那时题目一般会要求对 1e9+7 取模
        vector<long long> dp(len, 0);
        dp[0] = 1;                                  // 0 步：站在 0
        for (int step = 1; step <= n; ++step) {
            vector<long long> nxt(len, 0);
            for (int j = 0; j < len; ++j)
                nxt[j] = dp[(j - 1 + len) % len] + dp[(j + 1) % len];   // 从左右邻居走过来
            dp.swap(nxt);
        }
        return dp[0];
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { int n, len; long long expected; };
    vector<Case> cases = {
        {0, 10, 1},
        {1, 10, 0},
        {2, 10, 2},
        {3, 10, 0},       // 环长是偶数，奇数步回不去
        {4, 10, 6},       // C(4,2)，还绕不满一圈
        {10, 10, 254},    // C(10,5) = 252，再加顺时针、逆时针各绕一整圈 2 种
        {3, 3, 2},        // 环长 3：绕一整圈（顺/逆）
        {60, 10, 230585685502492596LL},   // n 的上限，long long 不溢出
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        long long got = sol.backToOrigin(c.n, c.len);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": n = " << c.n << ", 环长 = " << c.len << "\n  输出: " << got
             << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
