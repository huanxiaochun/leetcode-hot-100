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
    // 自底向上归并：每轮把长度为 step 的段两两合并，step = 1, 2, 4, ...
    ListNode* sortList(ListNode* head) {
        int n = 0;
        for (ListNode* p = head; p; p = p->next) ++n;
        ListNode dummy(0, head);
        for (int step = 1; step < n; step *= 2) {
            ListNode *tail = &dummy, *cur = dummy.next;   // tail：已合并部分的最后一个节点
            while (cur) {
                ListNode* left = cur;
                ListNode* right = split(left, step);      // 切出两段，各 step 个
                cur = split(right, step);
                tail = merge(left, right, tail);
            }
        }
        return dummy.next;
    }

private:
    // 从 head 起保留 n 个节点并断开，返回后面部分的头
    ListNode* split(ListNode* head, int n) {
        while (--n && head) head = head->next;
        if (!head) return nullptr;
        ListNode* rest = head->next;
        head->next = nullptr;
        return rest;
    }

    // 合并 a、b 接到 tail 后面，返回合并后的最后一个节点
    ListNode* merge(ListNode* a, ListNode* b, ListNode* tail) {
        while (a && b) {
            if (a->val <= b->val) tail->next = a, a = a->next;
            else tail->next = b, b = b->next;
            tail = tail->next;
        }
        tail->next = a ? a : b;
        while (tail->next) tail = tail->next;
        return tail;
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
