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
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* p = &dummy;
        while (p->next && p->next->next) {
            if (p->next->val == p->next->next->val) {
                int x = p->next->val;                       // 这个值整段删掉
                while (p->next && p->next->val == x) p->next = p->next->next;
            } else {
                p = p->next;                                // 唯一的，保留
            }
        }
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
        {{1, 2, 3, 3, 4, 4, 5}, {1, 2, 5}},
        {{1, 1, 1, 2, 3}, {2, 3}},
        {{}, {}},
        {{1, 1}, {}},
        {{1, 2, 2}, {1}},
        {{1, 2, 3}, {1, 2, 3}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.deleteDuplicates(build(c.in)));
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
