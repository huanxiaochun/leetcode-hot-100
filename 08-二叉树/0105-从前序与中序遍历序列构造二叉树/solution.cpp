/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pos.clear();
        for (int i = 0; i < inorder.size(); ++i) pos[inorder[i]] = i;  // 值 -> 在中序里的下标
        int p = 0;                                  // 前序里下一个要用的根
        return make(preorder, p, 0, inorder.size() - 1);
    }

private:
    unordered_map<int, int> pos;

    TreeNode* make(vector<int>& pre, int& p, int l, int r) {  // 建出中序 [l, r] 这一段对应的子树
        if (l > r) return nullptr;
        int v = pre[p++];                           // 前序是 根 左 右：最前面的就是根
        TreeNode* root = new TreeNode(v);
        int m = pos[v];                             // 中序里根的左边是左子树，右边是右子树
        root->left = make(pre, p, l, m - 1);        // 前序里左子树紧跟在根后面，所以先建左边
        root->right = make(pre, p, m + 1, r);
        return root;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
const int null = INT_MIN;                           // 测试数据里表示空节点

static void printTree(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << (i ? "," : "");
        if (v[i] == null) cout << "null";
        else cout << v[i];
    }
    cout << "]";
}

static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
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
        vector<int> pre, in, expected;
    };
    vector<Case> cases = {
        {{3, 9, 20, 15, 7}, {9, 3, 15, 20, 7}, {3, 9, 20, null, null, 15, 7}},
        {{-1}, {-1}, {-1}},
        {{1, 2}, {2, 1}, {1, 2}},
        {{1, 2}, {1, 2}, {1, null, 2}},
        {{1, 2, 4, 5, 3, 6}, {4, 2, 5, 1, 6, 3}, {1, 2, 3, 4, 5, 6}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toLevel(sol.buildTree(c.pre, c.in));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": preorder = ";
        printVec(c.pre);
        cout << ", inorder = ";
        printVec(c.in);
        cout << "\n  输出: ";
        printTree(got);
        cout << "   期望: ";
        printTree(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
