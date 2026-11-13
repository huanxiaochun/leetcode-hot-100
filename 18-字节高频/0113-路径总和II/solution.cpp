/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        ans.clear();                                // 同一个对象可能被调用多次
        path.clear();
        dfs(root, targetSum);
        return ans;
    }

private:
    vector<vector<int>> ans;
    vector<int> path;

    void dfs(TreeNode* node, int rest) {
        if (!node) return;
        path.push_back(node->val);
        rest -= node->val;
        if (!node->left && !node->right && rest == 0) ans.push_back(path);   // 叶子且刚好凑够
        dfs(node->left, rest);
        dfs(node->right, rest);
        path.pop_back();                            // 回溯
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
const int null = INT_MIN;                           // 测试数据里表示空节点

static TreeNode* build(const vector<int>& v) {      // 层序数组 -> 树
    if (v.empty() || v[0] == null) return nullptr;
    TreeNode* root = new TreeNode(v[0]);
    queue<TreeNode*> q;
    q.push(root);
    for (size_t i = 1; i < v.size(); i += 2) {
        TreeNode* cur = q.front(); q.pop();
        if (v[i] != null) q.push(cur->left = new TreeNode(v[i]));
        if (i + 1 < v.size() && v[i + 1] != null) q.push(cur->right = new TreeNode(v[i + 1]));
    }
    return root;
}
static void printTree(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ",";
        if (v[i] == null) cout << "null"; else cout << v[i];
    }
    cout << "]";
}
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
    struct Case { vector<int> tree; int target; vector<vector<int>> expected; };
    vector<Case> cases = {
        {{5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1}, 22, {{5, 4, 11, 2}, {5, 8, 4, 5}}},
        {{1, 2, 3}, 5, {}},
        {{1, 2}, 0, {}},
        {{}, 0, {}},
        {{-2, null, -3}, -5, {{-2, -3}}},          // 负数，不能按 rest<0 剪枝
        {{1, 2}, 1, {}},                           // 根不是叶子，不算
    };
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        Solution sol;                              // 每个用例用新对象，ans 不会串
        auto got = sol.pathSum(build(c.tree), c.target);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << ", targetSum = " << c.target << "\n  输出: "; printVecs(got);
        cout << "   期望: "; printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
