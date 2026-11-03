/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool row0 = false, col0 = false;            // 第 0 行 / 第 0 列本身有没有 0
        for (int j = 0; j < n; ++j) if (matrix[0][j] == 0) row0 = true;
        for (int i = 0; i < m; ++i) if (matrix[i][0] == 0) col0 = true;
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                if (matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;  // 用第 0 行、第 0 列当标记
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
        if (row0) for (int j = 0; j < n; ++j) matrix[0][j] = 0;  // 最后再处理第 0 行 / 列
        if (col0) for (int i = 0; i < m; ++i) matrix[i][0] = 0;
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
static void printVecs(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ",";
        printVec(v[i]);
    }
    cout << "]";
}

int main() {
    struct Case {
        vector<vector<int>> matrix;
        vector<vector<int>> expected;
    };
    vector<Case> cases = {
        {{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, {{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}},
        {{{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}}, {{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}}},
        {{{1}}, {{1}}},
        {{{1, 0}}, {{0, 0}}},
        {{{1, 2}, {3, 0}, {5, 6}}, {{1, 0}, {0, 0}, {5, 0}}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = c.matrix;                        // 原地修改，拷贝一份保留输入
        sol.setZeroes(got);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": matrix = ";
        printVecs(c.matrix);
        cout << "\n  输出: ";
        printVecs(got);
        cout << "\n  期望: ";
        printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
