/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<unsigned long long> dp(amount + 1, 0);   // 中间值可能超 int，题目保证答案在 int 内
        dp[0] = 1;
        for (int coin : coins)                          // 外层硬币 → 组合
            for (int j = coin; j <= amount; ++j)        // 金额从小到大 → 每种可无限用
                dp[j] += dp[j - coin];
        return (int)dp[amount];
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
    struct Case { int amount; vector<int> coins; int expected; };
    vector<Case> cases = {
        {5, {1, 2, 5}, 4},     // 5 / 2+2+1 / 2+1+1+1 / 1×5
        {3, {2}, 0},
        {10, {10}, 1},
        {0, {7}, 1},           // 什么都不选也算一种
        {4, {1, 2, 3}, 4},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.change(c.amount, c.coins);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": amount = " << c.amount << ", coins = "; printVec(c.coins);
        cout << "\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
