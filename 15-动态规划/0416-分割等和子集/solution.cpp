/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) return false;                  // 总和是奇数，分不成两半
        int target = sum / 2;
        // dp[j] = 用已经看过的数，能不能挑出几个凑成和 j
        vector<bool> dp(target + 1, false);
        dp[0] = true;                               // 一个都不挑，和是 0
        for (int x : nums)
            for (int j = target; j >= x; --j)       // 倒着走：每个数只能用一次
                if (dp[j - x]) dp[j] = true;        // 不用 x 已经能凑 j，或者凑出 j - x 再加上 x
        return dp[target];
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
        {{1, 5, 11, 5}, true},
        {{1, 2, 3, 5}, false},
        {{1, 1}, true},
        {{2, 2, 3, 5}, false},
        {{3, 3, 3, 4, 5}, true},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.canPartition(c.nums);
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
