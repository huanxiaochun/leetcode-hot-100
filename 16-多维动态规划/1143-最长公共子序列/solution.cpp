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
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        // dp[i][j]：text1 前 i 个字符和 text2 前 j 个字符的 LCS 长度；第 0 行 / 列是空串，都是 0
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;    // 最后一个字符相同：配成一对
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);   // 不同：扔掉其中一边的最后一个
            }
        }
        return dp[m][n];
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        string a, b;
        int expected;
    };
    vector<Case> cases = {
        {"abcde", "ace", 3},
        {"abc", "abc", 3},
        {"abc", "def", 0},
        {"bsbininm", "jmjkbkjkv", 1},
        {"oxcpqrsvwf", "shmtulqrypy", 2},
        {"a", "a", 1},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.longestCommonSubsequence(c.a, c.b);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": text1 = \"" << c.a << "\", text2 = \"" << c.b << "\"";
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
