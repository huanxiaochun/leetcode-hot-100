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
    int balancedStringSplit(string s) {
        int balance = 0, ans = 0;
        for (char c : s) {
            balance += c == 'R' ? 1 : -1;
            if (balance == 0) ++ans;                // 刚好平衡，切一刀
        }
        return ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { string s; int expected; };
    vector<Case> cases = {
        {"RLRRLLRLRL", 4},     // RL | RRLL | RL | RL
        {"RLRRRLLRLL", 2},     // RL | RRRLLRLL
        {"LLLLRRRR", 1},
        {"RLLLLRRRLR", 3},     // RL | LLLRRR | LR
        {"LR", 1},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.balancedStringSplit(c.s);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": s = \"" << c.s << "\"\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
