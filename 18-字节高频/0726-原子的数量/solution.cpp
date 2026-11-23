/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string countOfAtoms(string formula) {
        int i = 0, n = formula.size();
        auto num = [&] {                                    // 读数字，没有就是 1
            int k = 0;
            while (i < n && isdigit(formula[i])) k = k * 10 + (formula[i++] - '0');
            return k ? k : 1;
        };
        vector<map<string, int>> st(1);                     // 栈：每层括号一张表
        while (i < n) {
            if (formula[i] == '(') {
                st.push_back({});                           // 开新的一层
                ++i;
            } else if (formula[i] == ')') {
                ++i;
                int k = num();
                auto top = st.back();
                st.pop_back();
                for (auto& [a, c] : top) st.back()[a] += c * k;  // 乘 k 后并回上一层
            } else {
                string a(1, formula[i++]);                  // 大写字母开头
                while (i < n && islower(formula[i])) a += formula[i++];
                st.back()[a] += num();
            }
        }
        string ans;
        for (auto& [a, c] : st[0]) ans += a + (c > 1 ? to_string(c) : "");  // map 已按字典序
        return ans;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
int main() {
    struct Case { string formula, expected; };
    vector<Case> cases = {
        {"H2O", "H2O"},
        {"Mg(OH)2", "H2MgO2"},
        {"K4(ON(SO3)2)2", "K4N2O14S4"},
        {"Be32", "Be32"},
        {"((N42)24(OB40Li30CHe3O48LiNN26)33(C12Li48N30H13HBe31)21(BHN30Li26BCBe47N40)15(H5)16)14",
         "B18900Be18984C4200H5446He1386Li33894N50106O22638"},
        {"H50", "H50"},
        {"(H)", "H"},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        string got = sol.countOfAtoms(c.formula);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": formula = \"" << c.formula << "\"\n  输出: " << got
             << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
