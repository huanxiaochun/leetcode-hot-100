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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy;                             // 哨兵：不用单独处理头节点
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {               // 接上较小的那个
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;                  // 剩下的直接接上
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
        vector<int> l1, l2, expected;
    };
    vector<Case> cases = {
        {{1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4}},
        {{}, {}, {}},
        {{}, {0}, {0}},
        {{5}, {1, 2, 3}, {1, 2, 3, 5}},
        {{1, 1}, {1}, {1, 1, 1}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.mergeTwoLists(build(c.l1), build(c.l2)));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": l1 = ";
        printVec(c.l1);
        cout << ", l2 = ";
        printVec(c.l2);
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
