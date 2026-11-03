/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int top = 0, bottom = matrix.size() - 1;    // 四条边界，走完一条就往里收
        int left = 0, right = matrix[0].size() - 1;
        while (top <= bottom && left <= right) {
            for (int j = left; j <= right; ++j) ans.push_back(matrix[top][j]);     // 上：左 -> 右
            ++top;
            for (int i = top; i <= bottom; ++i) ans.push_back(matrix[i][right]);   // 右：上 -> 下
            --right;
            if (top <= bottom) {                    // 还剩行，才走下边
                for (int j = right; j >= left; --j) ans.push_back(matrix[bottom][j]);
                --bottom;
            }
            if (left <= right) {                    // 还剩列，才走左边
                for (int i = bottom; i >= top; --i) ans.push_back(matrix[i][left]);
                ++left;
            }
        }
        return ans;
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
        vector<int> expected;
    };
    vector<Case> cases = {
        {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, {1, 2, 3, 6, 9, 8, 7, 4, 5}},
        {{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}, {1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}},
        {{{1}}, {1}},
        {{{1, 2, 3}}, {1, 2, 3}},
        {{{1}, {2}, {3}}, {1, 2, 3}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.spiralOrder(c.matrix);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": matrix = ";
        printVecs(c.matrix);
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
