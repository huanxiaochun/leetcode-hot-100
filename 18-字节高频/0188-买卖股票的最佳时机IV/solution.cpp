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
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        // dp[i][j]：第 i 天结束时处于状态 j 的最大收益
        // j = 0 没操作；j 奇数 = 第 (j + 1) / 2 次买入后；j 偶数 = 第 j / 2 次卖出后
        vector<vector<int>> dp(n, vector<int>(2 * k + 1, 0));
        for (int j = 1; j < 2 * k; j += 2) dp[0][j] = -prices[0];    // 第 0 天买入
        for (int i = 1; i < n; ++i)
            for (int j = 1; j <= 2 * k; ++j) {
                int p = j % 2 ? -prices[i] : prices[i];             // 奇数买、偶数卖
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + p); // 不动 / 从上一个状态走过来
            }
        return dp[n - 1][2 * k];
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
    struct Case { int k; vector<int> prices; int expected; };
    vector<Case> cases = {
        {2, {2, 4, 1}, 2},
        {2, {3, 2, 6, 5, 0, 3}, 7},
        {1, {3, 2, 6, 5, 0, 3}, 4},
        {3, {1, 4, 2, 7, 3, 9}, 14},
        {2, {1}, 0},
        {4, {1, 2, 4, 2, 5, 7, 2, 4, 9, 0}, 15},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.maxProfit(c.k, c.prices);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": k = " << c.k << ", prices = "; printVec(c.prices);
        cout << "\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
