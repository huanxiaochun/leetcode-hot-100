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
    string addStrings(string num1, string num2) {
        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        string ans;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';
            ans.push_back('0' + sum % 10);          // 这一位
            carry = sum / 10;                       // 进位
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { string a, b, expected; };
    vector<Case> cases = {
        {"11", "123", "134"},
        {"456", "77", "533"},
        {"0", "0", "0"},
        {"999", "1", "1000"},
        {"1", "9999", "10000"},
        {"12345678901234567890", "98765432109876543210", "111111111011111111100"},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        string got = sol.addStrings(c.a, c.b);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": num1 = \"" << c.a << "\", num2 = \"" << c.b << "\"\n  输出: " << got
             << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
