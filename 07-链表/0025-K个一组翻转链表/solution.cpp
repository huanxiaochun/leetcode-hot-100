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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* pre = &dummy;                     // 上一组的尾巴
        while (true) {
            ListNode* tail = pre;
            for (int i = 0; i < k; ++i) {           // 往后数 k 个，不够就结束
                tail = tail->next;
                if (!tail) return dummy.next;
            }
            ListNode* nxt = tail->next;             // 下一组的开头
            ListNode *prev = nxt, *cur = pre->next; // 组内反转，第一个节点直接指向下一组
            while (cur != nxt) {
                ListNode* t = cur->next;
                cur->next = prev;
                prev = cur;
                cur = t;
            }
            ListNode* first = pre->next;            // 反转前的组头，现在是组尾
            pre->next = tail;                       // 接上反转后的组头
            pre = first;
        }
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
        int k;
        vector<int> expected;
    };
    vector<Case> cases = {
        {{1, 2, 3, 4, 5}, 2, {2, 1, 4, 3, 5}},
        {{1, 2, 3, 4, 5}, 3, {3, 2, 1, 4, 5}},
        {{1, 2, 3, 4}, 4, {4, 3, 2, 1}},
        {{1}, 1, {1}},
        {{1, 2, 3, 4, 5, 6}, 3, {3, 2, 1, 6, 5, 4}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.reverseKGroup(build(c.list), c.k));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printVec(c.list);
        cout << ", k = " << c.k << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
