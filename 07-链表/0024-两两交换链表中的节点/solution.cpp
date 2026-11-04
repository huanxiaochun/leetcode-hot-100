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
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0, head);
        ListNode* prev = &dummy;                    // 这一对前面的节点
        while (prev->next && prev->next->next) {
            ListNode *a = prev->next, *b = a->next;
            a->next = b->next;                      // ① a 指向下一对
            b->next = a;                            // ② b 指向 a
            prev->next = b;                         // ③ prev 指向 b
            prev = a;                               // 交换后 a 在后面，成为下一对的 prev
        }
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
        vector<int> list, expected;
    };
    vector<Case> cases = {
        {{1, 2, 3, 4}, {2, 1, 4, 3}},
        {{}, {}},
        {{1}, {1}},
        {{1, 2, 3}, {2, 1, 3}},
        {{1, 2, 3, 4, 5, 6}, {2, 1, 4, 3, 6, 5}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.swapPairs(build(c.list)));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.list);
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
