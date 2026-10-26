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
    vector<int> findAnagrams(string s, string p) {
        int m = p.size();
        vector<int> ans;
        if (s.size() < m) return ans;
        vector<int> need(26, 0), win(26, 0);       // p 的字母计数、窗口的字母计数
        for (char c : p) need[c - 'a']++;
        for (int r = 0; r < s.size(); ++r) {
            win[s[r] - 'a']++;                      // 右边进一个
            if (r >= m) win[s[r - m] - 'a']--;      // 左边出一个，窗口长度保持 m
            if (r >= m - 1 && win == need)          // 26 位比较，O(1)
                ans.push_back(r - m + 1);
        }
        return ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}

int main() {
    struct Case {
        string s, p;
        vector<int> expected;
    };
    vector<Case> cases = {
        {"cbaebabacd", "abc", {0, 6}},
        {"abab", "ab", {0, 1, 2}},
        {"a", "ab", {}},
        {"aaaa", "aa", {0, 1, 2}},
        {"baa", "aa", {1}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.findAnagrams(c.s, c.p);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\", p = \"" << c.p << "\"";
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
