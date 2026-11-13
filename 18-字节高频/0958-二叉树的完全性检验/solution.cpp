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
    bool isCompleteTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        bool seenNull = false;
        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();
            if (!cur) { seenNull = true; continue; }
            if (seenNull) return false;             // 空位后面又出现了节点
            q.push(cur->left);                      // 空孩子也入队
            q.push(cur->right);
        }
        return true;
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

int main() {
    struct Case { vector<int> tree; bool expected; };
    vector<Case> cases = {
        {{1, 2, 3, 4, 5, 6}, true},
        {{1, 2, 3, 4, 5, null, 7}, false},
        {{1, 2, 3, 4, null, 5}, false},       // 单看每个节点都不缺左孩子，但中间夹了空位
        {{1}, true},
        {{1, 2}, true},
        {{1, null, 2}, false},
        {{1, 2, 3, 4, 5, 6, 7}, true},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.isCompleteTree(build(c.tree));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << "\n  输出: " << (got ? "true" : "false") << "   期望: " << (c.expected ? "true" : "false")
             << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
