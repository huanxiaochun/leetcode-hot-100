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
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());                    // 排序后才能用双指针，也方便去重
        int n = nums.size();
        vector<vector<int>> ans;
        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] > 0) break;                        // 最小的都大于 0，后面不可能凑出 0
            if (i > 0 && nums[i] == nums[i - 1]) continue; // 第一个数去重
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum < 0) ++l;                          // 太小，左边换大的
                else if (sum > 0) --r;                     // 太大，右边换小的
                else {
                    ans.push_back({nums[i], nums[l], nums[r]});
                    while (l < r && nums[l] == nums[l + 1]) ++l;  // 跳过相同的第二个数
                    while (l < r && nums[r] == nums[r - 1]) --r;  // 跳过相同的第三个数
                    ++l, --r;
                }
            }
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

static void printVecs(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ",";
        printVec(v[i]);
    }
    cout << "]";
}

int main() {
    struct Case {
        vector<int> nums;
        vector<vector<int>> expected;
    };
    vector<Case> cases = {
        {{-1, 0, 1, 2, -1, -4}, {{-1, -1, 2}, {-1, 0, 1}}},
        {{0, 1, 1}, {}},
        {{0, 0, 0}, {{0, 0, 0}}},
        {{0, 0, 0, 0}, {{0, 0, 0}}},
        {{-2, 0, 1, 1, 2}, {{-2, 0, 2}, {-2, 1, 1}}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        vector<int> input = c.nums;                        // threeSum 会排序，留一份用来打印
        auto got = sol.threeSum(c.nums);
        sort(got.begin(), got.end());                      // 题目允许任意顺序
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(input);
        cout << "\n  输出: ";
        printVecs(got);
        cout << "   期望: ";
        printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
