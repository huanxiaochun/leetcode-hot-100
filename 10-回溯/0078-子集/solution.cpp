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

    // 下一个数只从 nums[start..] 里挑，保证子集里的下标递增，不会重复
    void dfs(vector<int>& nums, int start) {
        res.push_back(path);                        // 每个节点都是一个子集，一进来就收集
        for (int i = start; i < nums.size(); ++i) {
            path.push_back(nums[i]);                // 选 nums[i]
            dfs(nums, i + 1);                       // 再从它后面挑
            path.pop_back();                        // 撤销，换下一个
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        dfs(nums, 0);
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
        {{1, 2, 3}, {{}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2}, {2, 3}, {3}}},
        {{0}, {{}, {0}}},
        {{4, 9}, {{}, {4}, {4, 9}, {9}}},
        {{-1, 5, 2}, {{}, {-1}, {-1, 2}, {-1, 5}, {-1, 5, 2}, {2}, {5}, {5, 2}}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = Solution().subsets(c.nums);
        sort(got.begin(), got.end());               // 题目允许任意顺序
        sort(c.expected.begin(), c.expected.end());
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
