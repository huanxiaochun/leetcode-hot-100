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
    vector<vector<string>> res;
    vector<string> path;
    vector<vector<bool>> pal;                       // pal[i][j]：s[i..j] 是不是回文

    void dfs(const string& s, int start) {          // s[start..] 还没切
        if (start == s.size()) {                    // 切完了
            res.push_back(path);
            return;
        }
        for (int end = start; end < s.size(); ++end) {
            if (!pal[start][end]) continue;         // 剪枝：这一段不是回文，不能这么切
            path.push_back(s.substr(start, end - start + 1));
            dfs(s, end + 1);                        // 剩下的部分接着切
            path.pop_back();
        }
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        pal.assign(n, vector<bool>(n, true));
        // 两头相等，并且里面也是回文；i 从后往前，保证 pal[i + 1][j - 1] 先算好
        for (int i = n - 1; i >= 0; --i)
            for (int j = i + 1; j < n; ++j)
                pal[i][j] = s[i] == s[j] && pal[i + 1][j - 1];
        dfs(s, 0);
        return res;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

static void printParts(const vector<vector<string>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << (i ? "," : "") << "[";
        for (size_t j = 0; j < v[i].size(); ++j) cout << (j ? "," : "") << "\"" << v[i][j] << "\"";
        cout << "]";
    }
    cout << "]";
}

int main() {
    struct Case {
        string s;
        vector<vector<string>> expected;
    };
    vector<Case> cases = {
        {"aab", {{"a", "a", "b"}, {"aa", "b"}}},
        {"a", {{"a"}}},
        {"abba", {{"a", "b", "b", "a"}, {"a", "bb", "a"}, {"abba"}}},
        {"efe", {{"e", "f", "e"}, {"efe"}}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = Solution().partition(c.s);
        sort(got.begin(), got.end());               // 题目允许任意顺序
        sort(c.expected.begin(), c.expected.end());
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"\n  输出: ";
        printParts(got);
        cout << "\n  期望: ";
        printParts(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
