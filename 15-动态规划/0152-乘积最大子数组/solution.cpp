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
    int maxProduct(vector<int>& nums) {
        // mx / mn = 以当前数结尾的子数组，乘积最大 / 最小是多少
        // 要记最小：乘上一个负数，最小的会变成最大的
        int mx = nums[0], mn = nums[0], ans = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            int x = nums[i];
            int a = mx * x, b = mn * x;             // 接在前面那段后面
            mx = max({x, a, b});                    // 或者从 x 自己重新开始
            mn = min({x, a, b});
            ans = max(ans, mx);
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
        vector<int> nums;
        int expected;
    };
    vector<Case> cases = {
        {{2, 3, -2, 4}, 6},
        {{-2, 0, -1}, 0},
        {{-2, 3, -4}, 24},
        {{-2}, -2},
        {{0, 2}, 2},
        {{2, -5, -2, -4, 3}, 24},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.maxProduct(c.nums);
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
