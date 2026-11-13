/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int steps = 0;
        int end = 0;                                // 跳 steps 次能到的最远下标：这一层的右边界
        int far = 0;                                // 这一层里任意一格再跳一次，最远能到哪
        // 不用看最后一格：站到最后一格就已经到了，不必再起跳
        for (int i = 0; i + 1 < nums.size(); ++i) {
            far = max(far, i + nums[i]);
            if (i == end) {                         // 这一层走完了，必须再跳一次
                ++steps;
                end = far;                          // 下一层的右边界
            }
        }
        return steps;
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
        vector<int> nums;
        int expected;
    };
    vector<Case> cases = {
        {{2, 3, 1, 1, 4}, 2},                       // 0 -> 1 -> 4
        {{2, 3, 0, 1, 4}, 2},
        {{0}, 0},                                   // 已经在终点
        {{1, 2}, 1},
        {{1, 1, 1, 1}, 3},
        {{5, 1, 1, 1, 1}, 1},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.jump(c.nums);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
