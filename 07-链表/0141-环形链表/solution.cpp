/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

// LeetCode 已经定义好链表节点，本地运行需要自己写一份
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {                // 无环时 fast 会先走到 null
            slow = slow->next;                      // 走一步
            fast = fast->next->next;                // 走两步
            if (slow == fast) return true;          // 有环时 fast 一定会从后面追上 slow
        }
        return false;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}
// 建一条链，再把尾巴接到下标 pos 的节点上（pos = -1 表示无环）
static vector<ListNode*> buildCycle(const vector<int>& v, int pos) {
    vector<ListNode*> nodes;
    for (int x : v) nodes.push_back(new ListNode(x));
    for (size_t i = 0; i + 1 < nodes.size(); ++i) nodes[i]->next = nodes[i + 1];
    if (pos >= 0) nodes.back()->next = nodes[pos];
    return nodes;
}

int main() {
    struct Case {
        vector<int> list;
        int pos;
        bool expected;
    };
    vector<Case> cases = {
        {{3, 2, 0, -4}, 1, true},
        {{1, 2}, 0, true},
        {{1}, -1, false},
        {{1}, 0, true},
        {{1, 2, 3}, -1, false},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto nodes = buildCycle(c.list, c.pos);
        bool got = sol.hasCycle(nodes.empty() ? nullptr : nodes[0]);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.list);
        cout << ", pos = " << c.pos;
        cout << "\n  输出: " << boolalpha << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
