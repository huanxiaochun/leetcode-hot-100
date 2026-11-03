/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 1);
        for (int i = 1; i < n; ++i)
            ans[i] = ans[i - 1] * nums[i - 1];      // 先存左边所有数的乘积
        int right = 1;                              // 右边所有数的乘积
        for (int i = n - 1; i >= 0; --i) {
            ans[i] *= right;                        // 左积 × 右积
            right *= nums[i];
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
        vector<int> expected;
    };
    vector<Case> cases = {
        {{1, 2, 3, 4}, {24, 12, 8, 6}},
        {{-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0}},
        {{2, 3}, {3, 2}},
        {{0, 0, 5}, {0, 0, 0}},
        {{1, -1, 2, -2}, {4, -4, 2, -2}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.productExceptSelf(c.nums);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
