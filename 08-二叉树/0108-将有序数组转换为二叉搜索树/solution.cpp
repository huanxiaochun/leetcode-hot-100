/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return make(nums, 0, nums.size() - 1);
    }

private:
    TreeNode* make(vector<int>& nums, int l, int r) {   // 用 nums[l..r] 建一棵平衡 BST
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;                  // 中间的数当根，左右个数最多差 1
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = make(nums, l, mid - 1);        // 比它小的在左边
        root->right = make(nums, mid + 1, r);       // 比它大的在右边
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

static void inorder(TreeNode* t, vector<int>& out) {
    if (!t) return;
    inorder(t->left, out);
    out.push_back(t->val);
    inorder(t->right, out);
}

static int height(TreeNode* t) {                    // 不平衡时返回 -1
    if (!t) return 0;
    int l = height(t->left), r = height(t->right);
    if (l < 0 || r < 0 || abs(l - r) > 1) return -1;
    return 1 + max(l, r);
}

int main() {
    struct Case {
        vector<int> nums;
    };
    vector<Case> cases = {
        {{-10, -3, 0, 5, 9}},
        {{1, 3}},
        {{0}},
        {{1, 2, 3, 4, 5, 6, 7}},
        {{-5, -1, 2, 8}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        TreeNode* root = sol.sortedArrayToBST(c.nums);
        vector<int> in;
        inorder(root, in);
        bool ok = in == c.nums && height(root) >= 0;   // 答案不唯一：检查中序有序且高度平衡
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: ";
        printTree(toLevel(root));
        cout << (ok ? "（中序就是 nums，且高度平衡）" : "（不是平衡 BST）");
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
