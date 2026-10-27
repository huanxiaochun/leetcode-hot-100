/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> need(128, 0);                   // 还欠每个字符几个，负数表示多出来
        for (char c : t) need[c]++;
        int missing = t.size();                     // 还差几个字符没覆盖
        int start = 0, best = INT_MAX;
        for (int l = 0, r = 0; r < s.size(); ++r) {
            if (need[s[r]]-- > 0) --missing;        // 进来的是需要的字符
            while (missing == 0) {                  // 已经全覆盖，收缩左边
                if (r - l + 1 < best) best = r - l + 1, start = l;
                if (++need[s[l]] > 0) ++missing;    // 移出后又缺了，停止收缩
                ++l;
            }
        }
        return best == INT_MAX ? "" : s.substr(start, best);
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case {
        string s, t, expected;
    };
    vector<Case> cases = {
        {"ADOBECODEBANC", "ABC", "BANC"},
        {"a", "a", "a"},
        {"a", "aa", ""},
        {"aa", "aa", "aa"},
        {"ab", "b", "b"},
        {"cabwefgewcwaefgcf", "cae", "cwae"},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        string got = sol.minWindow(c.s, c.t);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\", t = \"" << c.t << "\"";
        cout << "\n  输出: \"" << got << "\"   期望: \"" << c.expected << "\"";
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
