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
        int n = nums.size();
        // mx[i] / mn[i] = 以 nums[i] 结尾的子数组，乘积最大 / 最小是多少
        // 要记最小：乘上一个负数，最小的会变成最大的
        vector<int> mx(n), mn(n);
        mx[0] = mn[0] = nums[0];                    // 以第一个数结尾的只有它自己
        int ans = nums[0];
        for (int i = 1; i < n; ++i) {
            int x = nums[i];
            int a = mx[i - 1] * x, b = mn[i - 1] * x;   // 接在以 nums[i - 1] 结尾的那段后面
            mx[i] = max({x, a, b});                 // 或者从 x 自己重新开始
            mn[i] = min({x, a, b});
            ans = max(ans, mx[i]);
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
