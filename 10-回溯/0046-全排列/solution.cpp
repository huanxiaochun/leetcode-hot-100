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
    vector<int> path;                               // 当前已经排好的前几位
    vector<bool> used;                              // used[i]：nums[i] 是否已经在 path 里

    void dfs(vector<int>& nums) {
        if (path.size() == nums.size()) {           // 每个数都用上了：得到一个排列
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;                  // 用过的不能再选
            used[i] = true;                         // 做选择
            path.push_back(nums[i]);
            dfs(nums);                              // 填下一位
            path.pop_back();                        // 撤销选择，换下一个数试
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        used.assign(nums.size(), false);
        dfs(nums);
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
        vector<int> nums;
        vector<vector<int>> expected;
    };
    vector<Case> cases = {
        {{1, 2, 3}, {{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}}},
        {{0, 1}, {{0, 1}, {1, 0}}},
        {{1}, {{1}}},
        {{5, -1, 4}, {{-1, 4, 5}, {-1, 5, 4}, {4, -1, 5}, {4, 5, -1}, {5, -1, 4}, {5, 4, -1}}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = Solution().permute(c.nums);
        sort(got.begin(), got.end());               // 题目允许任意顺序
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: ";
        printVecs(got);
        cout << "\n  期望: ";
        printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
