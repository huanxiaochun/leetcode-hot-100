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
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());             // 相同的挨在一起
        used.assign(nums.size(), false);
        ans.clear();
        path.clear();
        dfs(nums);
        return ans;
    }

private:
    vector<vector<int>> ans;
    vector<int> path;
    vector<bool> used;

    void dfs(const vector<int>& nums) {
        if (path.size() == nums.size()) { ans.push_back(path); return; }
        for (size_t i = 0; i < nums.size(); ++i) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;   // 相同数按顺序用
            used[i] = true;
            path.push_back(nums[i]);
            dfs(nums);
            path.pop_back();
            used[i] = false;
        }
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
    for (size_t i = 0; i < v.size(); ++i) { if (i) cout << ","; printVec(v[i]); }
    cout << "]";
}

int main() {
    vector<vector<int>> cases = {
        {1, 1, 2},
        {1, 2, 3},
        {2, 2, 1, 1},
        {1},
        {3, 3, 3},
        {1, 2, 2, 3, 3, 3},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto in = cases[k];
        auto got = sol.permuteUnique(in);
        // 期望：排序后用 next_permutation 枚举，天然不重复、按字典序
        vector<vector<int>> expected;
        auto a = cases[k];
        sort(a.begin(), a.end());
        do expected.push_back(a); while (next_permutation(a.begin(), a.end()));
        bool ok = got == expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = "; printVec(cases[k]);
        if (got.size() <= 6) { cout << "\n  输出: "; printVecs(got); }
        else cout << "\n  输出 " << got.size() << " 个排列";
        cout << "   期望 " << expected.size() << " 个" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
