/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());   // 按左端点排序
        vector<vector<int>> ans;
        for (auto& it : intervals) {
            if (!ans.empty() && it[0] <= ans.back()[1])
                ans.back()[1] = max(ans.back()[1], it[1]);  // 和上一段重叠，延长右端点
            else
                ans.push_back(it);                  // 不重叠，开新的一段
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
        vector<vector<int>> intervals;
        vector<vector<int>> expected;
    };
    vector<Case> cases = {
        {{{1, 3}, {2, 6}, {8, 10}, {15, 18}}, {{1, 6}, {8, 10}, {15, 18}}},
        {{{1, 4}, {4, 5}}, {{1, 5}}},
        {{{4, 7}, {1, 4}}, {{1, 7}}},
        {{{1, 10}, {2, 3}, {4, 5}}, {{1, 10}}},
        {{{5, 6}}, {{5, 6}}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto input = c.intervals;                   // merge 会排序，留一份用来打印
        auto got = sol.merge(c.intervals);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": intervals = ";
        printVecs(input);
        cout << "\n  输出: ";
        printVecs(got);
        cout << "   期望: ";
        printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
