/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> rows;
        for (int i = 0; i < numRows; ++i) {
            vector<int> row(i + 1, 1);              // 两头都是 1
            for (int j = 1; j < i; ++j)
                row[j] = rows[i - 1][j - 1] + rows[i - 1][j];   // 左上 + 正上
            rows.push_back(row);
        }
        return rows;
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
        int numRows;
        vector<vector<int>> expected;
    };
    vector<Case> cases = {
        {1, {{1}}},
        {2, {{1}, {1, 1}}},
        {5, {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}}},
        {6, {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}, {1, 5, 10, 10, 5, 1}}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.generate(c.numRows);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": numRows = " << c.numRows << "\n  输出: ";
        printVecs(got);
        cout << "\n  期望: ";
        printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
