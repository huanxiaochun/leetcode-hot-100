/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {      // slow 停在左中点
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* second = reverse(slow->next);
        slow->next = nullptr;                         // 断开前半段
        ListNode* first = head;
        while (second) {                              // 交替接：前、后、前、后……
            ListNode *n1 = first->next, *n2 = second->next;
            first->next = second;
            second->next = n1;
            first = n1;
            second = n2;
        }
    }

private:
    ListNode* reverse(ListNode* h) {
        ListNode* prev = nullptr;
        while (h) {
            ListNode* nxt = h->next;
            h->next = prev;
            prev = h;
            h = nxt;
        }
        return prev;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static ListNode* build(const vector<int>& v) {
    ListNode dummy, *p = &dummy;
    for (int x : v) p = p->next = new ListNode(x);
    return dummy.next;
}
static vector<int> toVec(ListNode* h) {
    vector<int> v;
    for (; h; h = h->next) v.push_back(h->val);
    return v;
}
static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}

int main() {
    struct Case { vector<int> in, expected; };
    vector<Case> cases = {
        {{1, 2, 3, 4}, {1, 4, 2, 3}},
        {{1, 2, 3, 4, 5}, {1, 5, 2, 4, 3}},
        {{1}, {1}},
        {{1, 2}, {1, 2}},
        {{1, 2, 3}, {1, 3, 2}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        ListNode* h = build(c.in);
        sol.reorderList(h);
        auto got = toVec(h);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.in);
        cout << "\n  输出: "; printVec(got);
        cout << "   期望: "; printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
