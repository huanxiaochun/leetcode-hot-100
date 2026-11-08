/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

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
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 0;
        depth(root);
        return ans;
    }

private:
    int ans = 0;

    int depth(TreeNode* node) {                     // 从 node 往下最多有几个节点
        if (!node) return 0;
        int l = depth(node->left), r = depth(node->right);
        ans = max(ans, l + r);                      // 拐点在 node 的最长路径有 l + r 条边
        return 1 + max(l, r);                       // 往上只能选一边
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

int main() {
    struct Case {
        vector<int> tree;
        int expected;
    };
    vector<Case> cases = {
        {{1, 2, 3, 4, 5}, 3},
        {{1, 2}, 1},
        {{1}, 0},
        {{1, 2, null, 3, 4, 5, null, null, 6}, 4},
        {{1, 2, 3, 4, null, null, 5, 6, null, null, 7}, 6},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.diameterOfBinaryTree(build(c.tree));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
