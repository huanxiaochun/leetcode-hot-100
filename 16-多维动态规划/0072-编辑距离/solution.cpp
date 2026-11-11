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
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        // dp[i][j]：把 word1 前 i 个字符变成 word2 前 j 个字符，最少要几步
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; ++i) dp[i][0] = i;  // 变成空串：全删掉
        for (int j = 0; j <= n; ++j) dp[0][j] = j;  // 空串变过去：一个个插入
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];    // 最后一个字符一样，不用动
                else
                    dp[i][j] = 1 + min({dp[i - 1][j - 1],   // 替换
                                        dp[i - 1][j],       // 删除 word1 的最后一个
                                        dp[i][j - 1]});     // 插入 word2 的最后一个
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
        {"horse", "ros", 3},
        {"intention", "execution", 5},
        {"", "abc", 3},
        {"abc", "", 3},
        {"abc", "abc", 0},
        {"kitten", "sitting", 3},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.minDistance(c.a, c.b);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": word1 = \"" << c.a << "\", word2 = \"" << c.b << "\"";
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
