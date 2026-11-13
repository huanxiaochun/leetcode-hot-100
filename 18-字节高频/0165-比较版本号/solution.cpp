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
    int compareVersion(string version1, string version2) {
        int m = version1.size(), n = version2.size(), i = 0, j = 0;
        while (i < m || j < n) {
            long long x = 0, y = 0;                         // 读完的串这一段就是 0
            for (; i < m && version1[i] != '.'; ++i) x = x * 10 + (version1[i] - '0');
            for (; j < n && version2[j] != '.'; ++j) y = y * 10 + (version2[j] - '0');
            if (x != y) return x > y ? 1 : -1;
            ++i, ++j;                                       // 跳过 '.'
        }
        return 0;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { string a, b; int expected; };
    vector<Case> cases = {
        {"1.2", "1.10", -1},       // 2 < 10，按字符串比会错
        {"1.01", "1.001", 0},
        {"1.0", "1.0.0.0", 0},
        {"0.1", "1.1", -1},
        {"1.0.1", "1", 1},
        {"7.5.2.4", "7.5.3", -1},
        {"1", "1.0.0.1", -1},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.compareVersion(c.a, c.b);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": version1 = \"" << c.a << "\", version2 = \"" << c.b << "\"\n  输出: " << got
             << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
