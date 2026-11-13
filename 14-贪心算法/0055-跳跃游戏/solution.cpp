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
    bool canJump(vector<int>& nums) {
        int far = 0;                                // 目前能到达的最远下标
        for (int i = 0; i < nums.size(); ++i) {
            if (i > far) return false;              // 走到了到不了的格子
            far = max(far, i + nums[i]);            // 从 i 出发最远能到 i + nums[i]
            if (far >= nums.size() - 1) return true;    // 已经能到最后一格
        }
        return true;
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
        bool expected;
    };
    vector<Case> cases = {
        {{2, 3, 1, 1, 4}, true},
        {{3, 2, 1, 0, 4}, false},                   // 每条路都会停在下标 3 的 0 上
        {{0}, true},                                // 起点就是终点
        {{0, 1}, false},
        {{2, 0, 0}, true},
        {{1, 1, 0, 1}, false},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.canJump(c.nums);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: " << boolalpha << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
