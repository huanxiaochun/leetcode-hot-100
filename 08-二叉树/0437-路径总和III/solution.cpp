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
    int pathSum(TreeNode* root, int targetSum) {
        cnt.clear();
        cnt[0] = 1;                                 // 空前缀：从根开始的路径也能被数到
        return dfs(root, 0, targetSum);
    }

private:
    unordered_map<long long, int> cnt;              // 根到当前节点这条路上，各前缀和出现几次

    int dfs(TreeNode* node, long long sum, int target) {   // 和可能超过 int，用 long long
        if (!node) return 0;
        sum += node->val;
        auto it = cnt.find(sum - target);
        int ans = it == cnt.end() ? 0 : it->second; // 以 node 结尾、和为 target 的路径条数
        cnt[sum]++;
        ans += dfs(node->left, sum, target);       // 下端在左子树里的
        ans += dfs(node->right, sum, target);      // 下端在右子树里的
        cnt[sum]--;                                 // 回溯：离开 node，它不再是后面节点的祖先
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
        int target;
        int expected;
    };
    vector<Case> cases = {
        {{10, 5, -3, 3, 2, null, 11, 3, -2, null, 1}, 8, 3},
        {{5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1}, 22, 3},
        {{}, 0, 0},
        {{1}, 1, 1},
        {{1000000000, 1000000000, null, 294967296, null, 1000000000, null, 1000000000, null, 1000000000}, 0, 0},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.pathSum(build(c.tree), c.target);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": root = ";
        printTree(c.tree);
        cout << ", target = " << c.target;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
