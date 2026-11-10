/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<pair<string, int>> st;                // 进 [ 之前的现场：外面已经拼好的串、这一段要重复几次
        string cur;                                 // 当前这一层正在拼的串
        int k = 0;                                  // 正在读的数字
        for (char c : s) {
            if (isdigit(c)) {
                k = k * 10 + (c - '0');             // 数字可能不止一位，比如 10[a]
            } else if (c == '[') {
                st.push({cur, k});                  // 保存现场，进入新的一层
                cur.clear();
                k = 0;
            } else if (c == ']') {
                auto [outer, times] = st.top();     // 按值取出来，下一行 pop 之后仍然有效
                st.pop();
                string rep;
                for (int i = 0; i < times; ++i) rep += cur;   // 这一层重复 times 次
                cur = outer + rep;                  // 接回到外面那一层后面
            } else {
                cur += c;
            }
        }
        return cur;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        string s, expected;
    };
    vector<Case> cases = {
        {"3[a]2[bc]", "aaabcbc"},
        {"3[a2[c]]", "accaccacc"},
        {"2[abc]3[cd]ef", "abcabccdcdcdef"},
        {"abc3[cd]xyz", "abccdcdcdxyz"},
        {"10[a]", "aaaaaaaaaa"},
        {"2[a2[b2[c]]]", "abccbccabccbcc"},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        string got = sol.decodeString(c.s);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"";
        cout << "\n  输出: \"" << got << "\"   期望: \"" << c.expected << "\"";
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
