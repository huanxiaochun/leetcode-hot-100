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
    int maxPathSum(TreeNode* root) {
        best = INT_MIN;                             // 节点值可能全是负数，不能从 0 开始
        gain(root);
        return best;
    }

private:
    int best = INT_MIN;

    int gain(TreeNode* node) {                      // 从 node 往下走一条路，最多能贡献多少
        if (!node) return 0;
        int l = max(0, gain(node->left));           // 贡献是负的，就不如不走那边
        int r = max(0, gain(node->right));
        best = max(best, node->val + l + r);        // 以 node 为最高点、两边都走的路径
        return node->val + max(l, r);               // 交给父节点时只能选一边
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
        {{1, 2, 3}, 6},
        {{-10, 9, 20, null, null, 15, 7}, 42},
        {{-3}, -3},
        {{2, -1}, 2},
        {{5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1}, 48},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.maxPathSum(build(c.tree));
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
