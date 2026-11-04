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
    ListNode* detectCycle(ListNode* head) {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {                     // 相遇了，一定有环
                ListNode* p = head;
                while (p != slow) {                 // 从头和从相遇点同时走，会在入口相遇
                    p = p->next;
                    slow = slow->next;
                }
                return p;
            }
        }
        return nullptr;
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
        int expected;                               // 入口的下标，-1 表示无环
    };
    vector<Case> cases = {
        {{3, 2, 0, -4}, 1, 1},
        {{1, 2}, 0, 0},
        {{1}, -1, -1},
        {{1}, 0, 0},
        {{1, 2, 3}, -1, -1},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto nodes = buildCycle(c.list, c.pos);
        ListNode* got = sol.detectCycle(nodes.empty() ? nullptr : nodes[0]);
        int idx = -1;
        for (size_t i = 0; i < nodes.size(); ++i)
            if (nodes[i] == got) idx = i;
        bool ok = idx == c.expected && (got != nullptr) == (c.expected >= 0);
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.list);
        cout << ", pos = " << c.pos;
        cout << "\n  输出: 下标 " << idx << "   期望: 下标 " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
