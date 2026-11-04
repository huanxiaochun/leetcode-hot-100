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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0, head);                    // 哨兵：删的是头节点也不用特判
        ListNode *fast = &dummy, *slow = &dummy;
        for (int i = 0; i < n; ++i)                 // fast 先走 n 步
            fast = fast->next;
        while (fast->next) {                        // 一起走，fast 到最后一个时 slow 在目标前一个
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* del = slow->next;
        slow->next = del->next;
        delete del;
        return dummy.next;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
// 测试用的节点不释放，程序结束时由系统回收
static ListNode* build(const vector<int>& v) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int x : v) tail = tail->next = new ListNode(x);
    return dummy.next;
}

static vector<int> toVec(ListNode* head) {
    vector<int> v;
    for (; head; head = head->next) v.push_back(head->val);
    return v;
}

static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}

int main() {
    struct Case {
        vector<int> list;
        int n;
        vector<int> expected;
    };
    vector<Case> cases = {
        {{1, 2, 3, 4, 5}, 2, {1, 2, 3, 5}},
        {{1}, 1, {}},
        {{1, 2}, 1, {1}},
        {{1, 2}, 2, {2}},
        {{1, 2, 3}, 3, {2, 3}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.removeNthFromEnd(build(c.list), c.n));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.list);
        cout << ", n = " << c.n << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
