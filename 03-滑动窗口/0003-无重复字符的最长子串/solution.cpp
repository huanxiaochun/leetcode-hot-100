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
    int lengthOfLongestSubstring(string s) {
        vector<int> last(128, -1);                  // 每个字符上次出现的下标
        int l = 0, best = 0;                        // 窗口 [l, r] 内没有重复字符
        for (int r = 0; r < s.size(); ++r) {
            char c = s[r];
            if (last[c] >= l) l = last[c] + 1;      // c 在窗口里出现过，左边界跳到它后面
            last[c] = r;
            best = max(best, r - l + 1);
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
        {"abcabcbb", 3},
        {"bbbbb", 1},
        {"pwwkew", 3},
        {"", 0},
        {"abba", 2},
        {"dvdf", 3},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.lengthOfLongestSubstring(c.s);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"";
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
