/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return true;
            if (nums[lo] == nums[mid]) {                // 分不清哪边有序，缩一格
                ++lo;
            } else if (nums[lo] < nums[mid]) {          // 左半有序
                if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
                else lo = mid + 1;
            } else {                                    // 右半有序
                if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return false;
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
    struct Case { vector<int> nums; int target; bool expected; };
    vector<Case> cases = {
        {{2, 5, 6, 0, 0, 1, 2}, 0, true},
        {{2, 5, 6, 0, 0, 1, 2}, 3, false},
        {{1, 0, 1, 1, 1}, 0, true},
        {{1, 1, 1, 0, 1}, 0, true},
        {{1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 13, true},
        {{1}, 0, false},
        {{3, 1}, 1, true},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.search(c.nums, c.target);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = "; printVec(c.nums);
        cout << ", target = " << c.target << "\n  输出: " << (got ? "true" : "false")
             << "   期望: " << (c.expected ? "true" : "false") << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }

    // 随机对拍：随机生成带重复的旋转数组，和 std::find 比
    mt19937 g(7);
    bool ok = true;
    for (int it = 0; it < 20000 && ok; ++it) {
        int n = g() % 12 + 1;
        vector<int> a(n);
        for (int& x : a) x = g() % 5;
        sort(a.begin(), a.end());
        rotate(a.begin(), a.begin() + g() % n, a.end());
        int t = g() % 6;
        if (sol.search(a, t) != (find(a.begin(), a.end(), t) != a.end())) ok = false;
    }
    passed += ok;
    cout << "用例 " << cases.size() + 1 << ": 随机对拍 2 万组（值域 0~4，重复很多）" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";

    int total = cases.size() + 1;
    cout << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}
