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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        while (!q.empty()) {
            int sz = q.size();                      // 这一层有几个
            vector<int> level;
            for (int i = 0; i < sz; ++i) {
                TreeNode* cur = q.front(); q.pop();
                level.push_back(cur->val);
                if (cur->left) q.push(cur->left);   // 入队顺序始终从左到右
                if (cur->right) q.push(cur->right);
            }
            if (!leftToRight) reverse(level.begin(), level.end());
            ans.push_back(level);
            leftToRight = !leftToRight;
        }
        return ans;
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
    struct Case { vector<int> tree; vector<vector<int>> expected; };
    vector<Case> cases = {
        {{3, 9, 20, null, null, 15, 7}, {{3}, {20, 9}, {15, 7}}},
        {{1}, {{1}}},
        {{}, {}},
        {{1, 2, 3, 4, 5, 6, 7}, {{1}, {3, 2}, {4, 5, 6, 7}}},
        {{1, 2, 3, 4, null, null, 5}, {{1}, {3, 2}, {4, 5}}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.zigzagLevelOrder(build(c.tree));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << "\n  输出: "; printVecs(got);
        cout << "   期望: "; printVecs(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
