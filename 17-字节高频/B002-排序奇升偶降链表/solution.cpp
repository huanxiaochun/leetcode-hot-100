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
    ListNode* sortOddEvenList(ListNode* head) {
        if (!head || !head->next) return head;
        // 1. 拆成奇链、偶链
        ListNode *odd = head, *evenHead = head->next, *even = evenHead;
        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = nullptr;
        // 2. 反转偶链，3. 合并
        return merge(head, reverse(evenHead));
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
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode dummy, *p = &dummy;
        while (a && b) {
            if (a->val <= b->val) { p->next = a; a = a->next; }
            else { p->next = b; b = b->next; }
            p = p->next;
        }
        p->next = a ? a : b;
        return dummy.next;
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
        {{1, 8, 3, 6, 5, 4, 7, 2}, {1, 2, 3, 4, 5, 6, 7, 8}},
        {{1, 8, 3, 6, 5, 4, 7, 2, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}},
        {{5}, {5}},
        {{2, 1}, {1, 2}},
        {{1, 9, 2, 3, 5}, {1, 2, 3, 5, 9}},   // 奇 1,2,5 升；偶 9,3 降
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.sortOddEvenList(build(c.in)));
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
