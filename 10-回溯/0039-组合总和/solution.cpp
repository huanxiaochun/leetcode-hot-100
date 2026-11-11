/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;

    // 还差 rest；只从 c[start..] 里挑，避免 [2,3] 和 [3,2] 这样的重复
    void dfs(vector<int>& c, int start, int rest) {
        if (rest == 0) {                            // 正好凑够
            res.push_back(path);
            return;
        }
        for (int i = start; i < c.size(); ++i) {
            if (c[i] > rest) break;                 // 剪枝：排过序，后面的只会更大
            path.push_back(c[i]);
            dfs(c, i, rest - c[i]);                 // 传 i 不是 i + 1：同一个数可以重复选
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // 先排序，剪枝才能直接 break
        dfs(candidates, 0, target);
        return res;
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
        vector<int> candidates;
        int target;
        vector<vector<int>> expected;
    };
    vector<Case> cases = {
        {{2, 3, 6, 7}, 7, {{2, 2, 3}, {7}}},
        {{2, 3, 5}, 8, {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}}},
        {{2}, 1, {}},
        {{7, 3, 2}, 18, {{2, 2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 3, 3}, {2, 2, 2, 2, 3, 7}, {2, 2, 2, 3, 3, 3, 3},
                         {2, 2, 7, 7}, {2, 3, 3, 3, 7}, {3, 3, 3, 3, 3, 3}}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto cand = c.candidates;
        auto got = Solution().combinationSum(cand, c.target);
        sort(got.begin(), got.end());               // 题目允许任意顺序
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": candidates = ";
        printVec(c.candidates);
        cout << ", target = " << c.target << "\n  输出: ";
        printVecs(got);
        cout << "\n  期望: ";
        printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
