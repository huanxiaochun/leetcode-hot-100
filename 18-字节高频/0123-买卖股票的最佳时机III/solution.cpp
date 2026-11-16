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
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // dp[i][j]：第 i 天结束时处于状态 j 的最大收益
        // 0 没操作，1 第一次买入后，2 第一次卖出后，3 第二次买入后，4 第二次卖出后
        vector<vector<int>> dp(n, vector<int>(5, 0));
        dp[0][1] = dp[0][3] = -prices[0];           // 第 0 天买入（买 → 卖 → 再买）
        for (int i = 1; i < n; ++i) {
            int p = prices[i];
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p);   // 不动 / 第一次买
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + p);   // 不动 / 第一次卖
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - p);   // 不动 / 第二次买
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + p);   // 不动 / 第二次卖
        }
        return dp[n - 1][4];                        // 只交易一次也包含在里面
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
    struct Case { vector<int> prices; int expected; };
    vector<Case> cases = {
        {{3, 3, 5, 0, 0, 3, 1, 4}, 6},
        {{1, 2, 3, 4, 5}, 4},
        {{7, 6, 4, 3, 1}, 0},
        {{1}, 0},
        {{1, 4, 2, 7, 3, 9}, 12},
        {{2, 1, 4, 5, 2, 9, 7}, 11},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.maxProfit(c.prices);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": prices = "; printVec(c.prices);
        cout << "\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
