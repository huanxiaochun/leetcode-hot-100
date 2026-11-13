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
    long long maxLessThan(vector<int> digits, long long n) {
        long long m = n - 1;                          // < n 变成 ≤ m
        if (m <= 0) return -1;
        string s = to_string(m);
        int L = s.size();
        sort(digits.begin(), digits.end());
        digits.erase(unique(digits.begin(), digits.end()), digits.end());
        bool have[10] = {};
        for (int d : digits) have[d] = true;
        char mx = '0' + digits.back();

        int i = 0;
        while (i < L && have[s[i] - '0']) ++i;        // 能照抄就照抄
        if (i == L) return m;                         // 每一位都拼得出

        for (int j = i; j >= 0; --j) {                // 从卡住的位置往前回退
            int lower = -1;
            for (int d : digits) if (d < s[j] - '0') lower = d;   // 比 s[j] 小的最大数字
            if (lower != -1)
                return stoll(s.substr(0, j) + char('0' + lower) + string(L - j - 1, mx));
        }
        return L > 1 ? stoll(string(L - 1, mx)) : -1; // 少一位，全填最大数字
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case {
        vector<int> digits;
        long long n, expected;
    };
    vector<Case> cases = {
        {{1, 2, 4, 9}, 2533, 2499},     // 5 不在集合，放 4，后面填 9
        {{1, 2, 4, 9}, 2411, 2299},     // m=2410：0、1 都没有更小的，退到 4 放 2
        {{1}, 1111, 111},               // 同位数拼不出，少一位
        {{2, 3}, 2, -1},                // m=1，一位都拼不出
        {{1, 2, 4, 9}, 100, 99},        // m=99 本身就能拼
        {{5, 7}, 50, 7},                // m=49：4 前没有更小的，少一位
        {{6, 7, 8}, 5555, 888},
        {{2, 4, 9}, 23122, 22999},      // 3 不在集合，第 2 位放 2
        {{9, 4, 2, 1}, 2533, 2499},     // 数字没排序、没去重也要对
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        long long got = sol.maxLessThan(c.digits, c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": digits = [";
        for (size_t t = 0; t < c.digits.size(); ++t) cout << (t ? "," : "") << c.digits[t];
        cout << "], n = " << c.n << "\n  输出: " << got << "   期望: " << c.expected
             << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
