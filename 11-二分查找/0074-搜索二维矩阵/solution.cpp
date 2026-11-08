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
        int m = matrix.size(), n = matrix[0].size();
        int l = 0, r = m * n;                       // 按行拼起来就是一个长度 m*n 的有序数组
        while (l < r) {
            int mid = l + (r - l) / 2;
            int x = matrix[mid / n][mid % n];       // 一维下标拆成行、列
            if (x == target) return true;
            if (x < target) l = mid + 1;
            else r = mid;
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
    vector<vector<int>> M = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    struct Case {
        vector<vector<int>> matrix;
        int target;
        bool expected;
    };
    vector<Case> cases = {
        {M, 3, true},
        {M, 13, false},
        {M, 60, true},
        {{{1}}, 1, true},
        {{{1}, {3}}, 2, false},
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
