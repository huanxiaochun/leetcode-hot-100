/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = 0, j = matrix[0].size() - 1;        // 从右上角出发
        while (i < matrix.size() && j >= 0) {
            int x = matrix[i][j];
            if (x == target) return true;
            if (x > target) --j;                    // 这一列往下都更大，整列排除
            else ++i;                               // 这一行往左都更小，整行排除
        }
        return false;
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
    vector<vector<int>> M = {
        {1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}};
    struct Case {
        vector<vector<int>> matrix;
        int target;
        bool expected;
    };
    vector<Case> cases = {
        {M, 5, true},
        {M, 20, false},
        {M, 30, true},
        {M, 0, false},
        {{{-5}}, -5, true},
        {{{1, 3, 5}}, 4, false},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.searchMatrix(c.matrix, c.target);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": matrix = ";
        printVecs(c.matrix);
        cout << ", target = " << c.target;
        cout << "\n  输出: " << boolalpha << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
