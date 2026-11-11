/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int maxLen = 0;                             // 最长的词：最后一个词不会比它长
        for (auto& w : wordDict) maxLen = max<int>(maxLen, w.size());
        int n = s.size();
        // dp[i] = s 的前 i 个字符能不能拆成字典里的词
        vector<bool> dp(n + 1, false);
        dp[0] = true;                               // 空串：什么都不拆
        for (int i = 1; i <= n; ++i)
            for (int j = i - 1; j >= 0 && i - j <= maxLen; --j)   // 最后一个词是 s[j, i)
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
        return dp[n];
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        string s;
        vector<string> dict;
        bool expected;
    };
    vector<Case> cases = {
        {"leetcode", {"leet", "code"}, true},
        {"applepenapple", {"apple", "pen"}, true},
        {"catsandog", {"cats", "dog", "sand", "and", "cat"}, false},
        {"aaaaaaa", {"aaaa", "aaa"}, true},
        {"cars", {"car", "ca", "rs"}, true},
        {"ab", {"a"}, false},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.wordBreak(c.s, c.dict);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\", wordDict = [";
        for (size_t i = 0; i < c.dict.size(); ++i) cout << (i ? "," : "") << "\"" << c.dict[i] << "\"";
        cout << "]\n  输出: " << boolalpha << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
