/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX, ans = 0;
        for (int p : prices) {
            minPrice = min(minPrice, p);            // 到今天为止的最低价
            ans = max(ans, p - minPrice);           // 今天卖能赚多少
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
        vector<int> prices;
        int expected;
    };
    vector<Case> cases = {
        {{7, 1, 5, 3, 6, 4}, 5},
        {{7, 6, 4, 3, 1}, 0},
        {{1}, 0},
        {{2, 4, 1}, 2},                             // 最低价 1 在最后一天，买了也卖不掉
        {{3, 2, 6, 5, 0, 3}, 4},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.maxProfit(c.prices);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": prices = ";
        printVec(c.prices);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
