/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<vector<string>> res;
    vector<string> board;
    // 每行只放一个，所以只要检查列和两条对角线
    // 同一条「/」对角线上 r + c 相同；同一条「\」对角线上 r - c 相同，加 n - 1 变成非负下标
    vector<bool> col, d1, d2;
    int n;

    void dfs(int r) {                               // 给第 r 行找位置
        if (r == n) {                               // n 行都放好了
            res.push_back(board);
            return;
        }
        for (int c = 0; c < n; ++c) {
            if (col[c] || d1[r + c] || d2[r - c + n - 1]) continue;   // 剪枝：会被攻击
            board[r][c] = 'Q';                      // 做选择
            col[c] = d1[r + c] = d2[r - c + n - 1] = true;
            dfs(r + 1);                             // 去放下一行
            board[r][c] = '.';                      // 撤销选择
            col[c] = d1[r + c] = d2[r - c + n - 1] = false;
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        board.assign(n, string(n, '.'));
        col.assign(n, false);
        d1.assign(2 * n - 1, false);
        d2.assign(2 * n - 1, false);
        dfs(0);
        return res;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        int n;
        vector<vector<string>> expected;
    };
    vector<Case> cases = {
        {4, {{".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}}},
        {1, {{"Q"}}},
        {2, {}},
        {3, {}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = Solution().solveNQueens(c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": n = " << c.n << "\n  输出: " << got.size() << " 种摆法";
        for (auto& b : got) {
            cout << "\n   ";
            for (auto& row : b) cout << " " << row;
        }
        cout << "\n  期望: " << c.expected.size() << " 种摆法";
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
