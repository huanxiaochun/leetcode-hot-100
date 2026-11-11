/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
    // 从 (i, j) 出发，能不能拼出 word[k..]
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int k) {
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size()) return false;   // 出界
        if (board[i][j] != word[k]) return false;   // 字母不对（走过的格子是 '#'，也不会相等）
        if (k == word.size() - 1) return true;      // 最后一个字母也对上了
        char c = board[i][j];
        board[i][j] = '#';                          // 做选择：标记走过，不能再踩
        bool found = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i - 1, j, k + 1) ||
                     dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i, j - 1, k + 1);
        board[i][j] = c;                            // 撤销选择：恢复原字母
        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); ++i)
            for (int j = 0; j < board[0].size(); ++j)
                if (dfs(board, word, i, j, 0)) return true;   // 每个格子都可以当起点
        return false;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        vector<vector<char>> board;
        string word;
        bool expected;
    };
    vector<vector<char>> b = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    vector<Case> cases = {
        {b, "ABCCED", true},
        {b, "SEE", true},
        {b, "ABCB", false},
        {{{'a'}}, "a", true},
        {{{'a', 'a'}}, "aaa", false},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = Solution().exist(c.board, c.word);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": board = [";
        for (size_t i = 0; i < c.board.size(); ++i) cout << (i ? "," : "") << string(c.board[i].begin(), c.board[i].end());
        cout << "], word = \"" << c.word << "\"";
        cout << "\n  输出: " << boolalpha << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
