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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        ListNode* pre = &dummy;
        for (int i = 1; i < left; ++i) pre = pre->next;   // 停在第 left-1 个
        ListNode* cur = pre->next;
        for (int i = 0; i < right - left; ++i) {
            ListNode* nxt = cur->next;                     // 摘下 cur 后面那个
            cur->next = nxt->next;
            nxt->next = pre->next;                         // 插到 pre 后面
            pre->next = nxt;
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
    struct Case { vector<int> in; int left, right; vector<int> expected; };
    vector<Case> cases = {
        {{1, 2, 3, 4, 5}, 2, 4, {1, 4, 3, 2, 5}},
        {{5}, 1, 1, {5}},
        {{1, 2, 3, 4, 5}, 1, 5, {5, 4, 3, 2, 1}},
        {{1, 2, 3}, 1, 2, {2, 1, 3}},
        {{1, 2, 3}, 3, 3, {1, 2, 3}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.reverseBetween(build(c.in), c.left, c.right));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.in);
        cout << ", left = " << c.left << ", right = " << c.right << "\n  输出: "; printVec(got);
        cout << "   期望: "; printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
