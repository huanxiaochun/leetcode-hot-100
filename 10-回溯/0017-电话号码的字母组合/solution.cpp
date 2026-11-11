/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    const vector<string> keys = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string path;

    void dfs(const string& digits, int i) {         // 第 i 位数字选哪个字母
        if (i == digits.size()) {                   // 每一位都选好了
            res.push_back(path);
            return;
        }
        for (char c : keys[digits[i] - '0']) {
            path.push_back(c);                      // 这一位选 c
            dfs(digits, i + 1);                     // 去选下一位
            path.pop_back();                        // 撤销，换这个按键上的下一个字母
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};              // 空串要返回空列表，不是 {""}
        dfs(digits, 0);
        return res;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printStrs(const vector<string>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << "\"" << v[i] << "\"";
    cout << "]";
}

int main() {
    struct Case {
        string digits;
        vector<string> expected;
    };
    vector<Case> cases = {
        {"23", {"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}},
        {"", {}},
        {"2", {"a", "b", "c"}},
        {"79", {"pw", "px", "py", "pz", "qw", "qx", "qy", "qz", "rw", "rx", "ry", "rz", "sw", "sx", "sy", "sz"}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = Solution().letterCombinations(c.digits);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": digits = \"" << c.digits << "\"\n  输出: ";
        printStrs(got);
        cout << "\n  期望: ";
        printStrs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
