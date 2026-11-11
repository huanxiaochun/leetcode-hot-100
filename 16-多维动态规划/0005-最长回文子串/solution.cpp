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
    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));   // dp[i][j]：s[i..j] 是不是回文
        int start = 0, len = 1;
        for (int i = n - 1; i >= 0; --i) {          // i 从大到小：用到的 dp[i+1][..] 已经算好
            for (int j = i; j < n; ++j) {
                // 两头相等，并且中间 s[i+1..j-1] 也是回文（长度 <= 2 时中间是空的或只有一个字）
                if (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    if (j - i + 1 > len) {          // 更长，记下来
                        start = i;
                        len = j - i + 1;
                    }
                }
            }
        }
        return s.substr(start, len);
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

static bool isPal(const string& t) {
    for (size_t i = 0, j = t.size(); i + 1 < j; ++i, --j)
        if (t[i] != t[j - 1]) return false;
    return true;
}

int main() {
    struct Case {
        string s, expected;
    };
    vector<Case> cases = {
        {"babad", "bab"},
        {"cbbd", "bb"},
        {"a", "a"},
        {"ac", "a"},
        {"forgeeksskeegfor", "geeksskeeg"},
        {"aaaa", "aaaa"},
        {"abacdfgdcaba", "aba"},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        string got = sol.longestPalindrome(c.s);
        // 一样长的回文可能不止一个，都算对
        bool ok = got.size() == c.expected.size() && isPal(got) && c.s.find(got) != string::npos;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"";
        cout << "\n  输出: \"" << got << "\"   期望: \"" << c.expected << "\"";
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
