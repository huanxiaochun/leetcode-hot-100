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
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 1;
        // dp[i] = 以 nums[i] 结尾的最长递增子序列的长度
        vector<int> dp(n, 1);                       // 每个数自己就是长度 1
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j)             // 看 i 左边的每一个数
                if (nums[j] < nums[i])              // 比 nums[i] 小，nums[i] 能接在它后面
                    dp[i] = max(dp[i], dp[j] + 1);
            ans = max(ans, dp[i]);                  // 最长的不一定以最后一个数结尾
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
        {{10, 9, 2, 5, 3, 7, 101, 18}, 4},
        {{0, 1, 0, 3, 2, 3}, 4},
        {{7, 7, 7, 7}, 1},
        {{5}, 1},
        {{4, 10, 4, 3, 8, 9}, 3},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.lengthOfLIS(c.nums);
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
