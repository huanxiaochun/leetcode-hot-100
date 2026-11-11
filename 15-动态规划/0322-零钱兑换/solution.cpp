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
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] = 凑出金额 i 最少要几枚硬币
        // amount + 1 枚不可能用到，当作「凑不出」
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i)
            for (int c : coins)                     // 最后一枚用面值 c
                if (c <= i) dp[i] = min(dp[i], dp[i - c] + 1);
        return dp[amount] > amount ? -1 : dp[amount];
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
        vector<int> coins;
        int amount, expected;
    };
    vector<Case> cases = {
        {{1, 2, 5}, 11, 3},
        {{2}, 3, -1},
        {{1}, 0, 0},
        {{2, 5, 10, 1}, 27, 4},
        {{186, 419, 83, 408}, 6249, 20},
        {{3, 7}, 5, -1},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.coinChange(c.coins, c.amount);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": coins = ";
        printVec(c.coins);
        cout << ", amount = " << c.amount;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
