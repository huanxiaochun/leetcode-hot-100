/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), best = 0;
        // dp[i] = 以 s[i] 结尾的最长有效括号子串的长度；以 ( 结尾的一定是 0
        vector<int> dp(n, 0);
        for (int i = 1; i < n; ++i) {
            if (s[i] == '(') continue;
            int j = i - 1 - dp[i - 1];              // 跳过 i - 1 结尾的那一段，看它前面那个字符
            if (j >= 0 && s[j] == '(') {
                dp[i] = dp[i - 1] + 2;              // s[j] 和 s[i] 配成一对，把中间那段包起来
                if (j >= 1) dp[i] += dp[j - 1];     // 再接上 j 前面紧挨着的那一段
            }
            best = max(best, dp[i]);
        }
        return best;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        string s;
        int expected;
    };
    vector<Case> cases = {
        {"(()", 2},
        {")()())", 4},
        {"", 0},
        {"()(())", 6},
        {"(()())", 6},
        {"())((())", 4},
        {"((((", 0},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.longestValidParentheses(c.s);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"";
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
