/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// LeetCode 已经定义好树节点，本地运行需要自己写一份
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
    // 返回值的含义：在 root 这棵子树里找 p、q
    //   p、q 都在里面 -> 返回它们的最近公共祖先
    //   只有一个在     -> 返回那一个
    //   都不在         -> 返回 nullptr
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 空树什么都没有；root 自己就是 p 或 q，直接把自己报上去，不用再往下找：
        // 如果另一个在它下面，它就是答案；如果另一个在别处，上面的节点会发现
        if (!root || root == p || root == q) return root;
        TreeNode* l = lowestCommonAncestor(root->left, p, q);   // 左子树找到了什么
        TreeNode* r = lowestCommonAncestor(root->right, p, q);  // 右子树找到了什么
        if (l && r) return root;                    // 一边一个：p、q 分在 root 两侧，root 就是答案
        return l ? l : r;                           // 只有一边有结果（可能是 p、q 之一，也可能是已经找到的答案）：原样往上传
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
        TreeNode* cur = q.front();
        q.pop();
        if (v[i] != null) q.push(cur->left = new TreeNode(v[i]));
        if (i + 1 < v.size() && v[i + 1] != null) q.push(cur->right = new TreeNode(v[i + 1]));
    }
    return root;
}

static void printTree(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << (i ? "," : "");
        if (v[i] == null) cout << "null";
        else cout << v[i];
    }
    cout << "]";
}

static TreeNode* findNode(TreeNode* root, int v) {
    if (!root || root->val == v) return root;
    TreeNode* l = findNode(root->left, v);
    return l ? l : findNode(root->right, v);
}

int main() {
    struct Case {
        vector<int> tree;
        int p, q, expected;
    };
    vector<int> T = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
    vector<Case> cases = {
        {T, 5, 1, 3},
        {T, 5, 4, 5},
        {{1, 2}, 1, 2, 1},
        {T, 7, 8, 3},
        {T, 6, 4, 5},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        TreeNode* root = build(c.tree);
        TreeNode* got = sol.lowestCommonAncestor(root, findNode(root, c.p), findNode(root, c.q));
        bool ok = got == findNode(root, c.expected);    // 比较的是节点本身
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << ", p = " << c.p << ", q = " << c.q;
        cout << "\n  输出: " << (got ? got->val : null) << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
