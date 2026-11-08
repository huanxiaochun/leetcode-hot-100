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
    // 归并排序：从中间切成两半，各自排好，再合并
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;      // 0 或 1 个节点，本身有序
        ListNode *slow = head, *fast = head->next;  // fast 先走一步：偶数个时 slow 停在左中点
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* right = slow->next;               // 从中间切断
        slow->next = nullptr;
        return merge(sortList(head), sortList(right));
    }

private:
    ListNode* merge(ListNode* a, ListNode* b) {     // 合并两个有序链表（21 题）
        ListNode dummy;
        ListNode* tail = &dummy;
        while (a && b) {
            if (a->val <= b->val) tail->next = a, a = a->next;   // <= 保证稳定
            else tail->next = b, b = b->next;
            tail = tail->next;
        }
        tail->next = a ? a : b;
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
        {{4, 2, 1, 3}, {1, 2, 3, 4}},
        {{-1, 5, 3, 4, 0}, {-1, 0, 3, 4, 5}},
        {{}, {}},
        {{1}, {1}},
        {{3, 3, 1, 2, 1}, {1, 1, 2, 3, 3}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = toVec(sol.sortList(build(c.list)));
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
