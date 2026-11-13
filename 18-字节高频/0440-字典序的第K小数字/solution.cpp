/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthNumber(int n, int k) {
        long long cur = 1;
        --k;                                        // cur = 1 本身算一个
        while (k > 0) {
            long long steps = count(cur, n);
            if (steps <= k) {                       // 整棵子树跳过，去右兄弟
                k -= steps;
                ++cur;
            } else {                                // 答案在子树里，往下一层
                cur *= 10;
                --k;
            }
        }
        return (int)cur;
    }

private:
    // 以 cur 为根、值不超过 n 的子树有多少个数
    long long count(long long cur, long long n) {
        long long steps = 0, first = cur, last = cur;
        while (first <= n) {
            steps += min(last, n) - first + 1;      // 这一层落在 [first, min(last, n)]
            first = first * 10;
            last = last * 10 + 9;
        }
        return steps;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { int n, k, expected; };
    vector<Case> cases = {
        {13, 2, 10}, {1, 1, 1}, {13, 6, 2}, {100, 10, 17}, {10, 3, 2},
        {1000000000, 1000000000, 999999999},
    };
    Solution sol;
    int passed = 0;
    for (size_t t = 0; t < cases.size(); ++t) {
        auto& c = cases[t];
        int got = sol.findKthNumber(c.n, c.k);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << t + 1 << ": n = " << c.n << ", k = " << c.k << "\n  输出: " << got
             << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }

    // 暴力对拍：n ≤ 300 的所有 k，和「转字符串排序」的结果比
    bool ok = true;
    for (int n = 1; n <= 300 && ok; ++n) {
        vector<string> v;
        for (int x = 1; x <= n; ++x) v.push_back(to_string(x));
        sort(v.begin(), v.end());
        for (int k = 1; k <= n; ++k)
            if (sol.findKthNumber(n, k) != stoi(v[k - 1])) { ok = false; break; }
    }
    passed += ok;
    cout << "用例 " << cases.size() + 1 << ": 暴力对拍 n = 1~300 的全部 k" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";

    int total = cases.size() + 1;
    cout << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}
