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
    void flatten(TreeNode* root) {
        for (TreeNode* cur = root; cur; cur = cur->right) {
            if (!cur->left) continue;
            TreeNode* pre = cur->left;
            while (pre->right) pre = pre->right;    // 左子树最右边的节点：前序里它后面紧跟着 cur->right
            pre->right = cur->right;                // 右子树接到它后面
            cur->right = cur->left;                 // 左子树整个挪到右边
            cur->left = nullptr;
        }
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

static vector<int> toLevel(TreeNode* root) {      // 树 -> 层序数组，去掉末尾的 null
    vector<int> out;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();
        if (!cur) {
            out.push_back(null);
            continue;
        }
        out.push_back(cur->val);
        q.push(cur->left);
        q.push(cur->right);
    }
    while (!out.empty() && out.back() == null) out.pop_back();
    return out;
}

int main() {
    struct Case {
        vector<int> tree, expected;
    };
    vector<Case> cases = {
        {{1, 2, 5, 3, 4, null, 6}, {1, null, 2, null, 3, null, 4, null, 5, null, 6}},
        {{}, {}},
        {{0}, {0}},
        {{1, 2, 3}, {1, null, 2, null, 3}},
        {{1, null, 2, 3}, {1, null, 2, null, 3}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        TreeNode* root = build(c.tree);
        sol.flatten(root);
        auto got = toLevel(root);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << "\n  输出: ";
        printTree(got);
        cout << "   期望: ";
        printTree(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
