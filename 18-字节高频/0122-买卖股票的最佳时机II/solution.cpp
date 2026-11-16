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
        vector<vector<int>> dp(n, vector<int>(2));  // dp[i][0] 不持有，dp[i][1] 持有
        dp[0][0] = 0;                               // 第 0 天什么都不做
        dp[0][1] = -prices[0];                      // 第 0 天买入
        for (int i = 1; i < n; ++i) {
            int p = prices[i];
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + p);   // 不动 / 今天卖
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p);   // 不动 / 今天买
        }
        return dp[n - 1][0];                        // 最后手里没股票
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
        {{7, 1, 5, 3, 6, 4}, 7},
        {{1, 2, 3, 4, 5}, 4},
        {{7, 6, 4, 3, 1}, 0},
        {{1}, 0},
        {{2, 1, 2, 0, 1}, 2},
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
