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
    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) --i;      // 1. 第一个「下降点」
        if (i >= 0) {
            int j = n - 1;
            while (nums[j] <= nums[i]) --j;                 // 2. 右边比它大的最小者
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());          // 3. 后缀变升序（i=-1 时整体反转）
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
    struct Case { vector<int> nums, expected; };
    vector<Case> cases = {
        {{1, 2, 3}, {1, 3, 2}},
        {{3, 2, 1}, {1, 2, 3}},
        {{1, 1, 5}, {1, 5, 1}},
        {{1}, {1}},
        {{1, 5, 8, 4, 7, 6, 5, 3, 1}, {1, 5, 8, 5, 1, 3, 4, 6, 7}},
        {{1, 3, 2}, {2, 1, 3}},
        {{2, 3, 1, 3, 3}, {2, 3, 3, 1, 3}},   // 有重复元素
        {{5, 1, 1}, {1, 1, 5}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = c.nums;
        sol.nextPermutation(got);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = "; printVec(c.nums);
        cout << "\n  输出: "; printVec(got);
        cout << "   期望: "; printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
