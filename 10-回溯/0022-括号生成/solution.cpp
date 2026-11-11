/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<string> res;
    string path;

    // open / close：已经放了几个左括号、几个右括号
    void dfs(int n, int open, int close) {
        if (path.size() == 2 * n) {                 // 放满 2n 个，一定合法
            res.push_back(path);
            return;
        }
        if (open < n) {                             // 左括号还没用完，就可以放
            path.push_back('(');
            dfs(n, open + 1, close);
            path.pop_back();
        }
        if (close < open) {                         // 右括号不能比左括号多
            path.push_back(')');
            dfs(n, open, close + 1);
            path.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n) {
        dfs(n, 0, 0);
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
        int n;
        vector<string> expected;
    };
    vector<Case> cases = {
        {3, {"((()))", "(()())", "(())()", "()(())", "()()()"}},
        {1, {"()"}},
        {2, {"(())", "()()"}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = Solution().generateParenthesis(c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": n = " << c.n << "\n  输出: ";
        printStrs(got);
        cout << "\n  期望: ";
        printStrs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
