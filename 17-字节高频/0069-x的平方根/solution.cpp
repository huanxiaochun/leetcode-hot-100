/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        long long lo = 0, hi = x, ans = 0;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (mid * mid <= x) {                   // long long，防溢出
                ans = mid;                          // 可行，再往右试
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return (int)ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { int x, expected; };
    vector<Case> cases = {
        {4, 2}, {8, 2}, {0, 0}, {1, 1}, {2, 1}, {15, 3}, {16, 4},
        {2147395599, 46339}, {2147483647, 46340},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.mySqrt(c.x);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": x = " << c.x << "\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
