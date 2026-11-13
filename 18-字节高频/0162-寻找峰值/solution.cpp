/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] < nums[mid + 1]) lo = mid + 1;   // 右边是上坡，峰在右边
            else hi = mid;                                  // mid 可能就是峰
        }
        return lo;
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

// 答案不唯一，只要是峰就算对
static bool isPeak(const vector<int>& a, int i) {
    int n = a.size();
    if (i < 0 || i >= n) return false;
    return (i == 0 || a[i] > a[i - 1]) && (i == n - 1 || a[i] > a[i + 1]);
}

int main() {
    vector<vector<int>> cases = {
        {1, 2, 3, 1},
        {1, 2, 1, 3, 5, 6, 4},
        {1},
        {1, 2},
        {2, 1},
        {5, 4, 3, 2, 1},
        {1, 2, 3, 4, 5},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& nums = cases[k];
        int got = sol.findPeakElement(nums);
        bool ok = isPeak(nums, got);
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = "; printVec(nums);
        cout << "\n  输出: " << got << "   （nums[" << got << "] 是峰）" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
