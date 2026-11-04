/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>
#include <string>

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
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode *a = headA, *b = headB;
        while (a != b) {                            // 两人都走 A + B 的总长度，会在交点（或 null）相遇
            a = a ? a->next : headB;                // 走完 A 换到 B
            b = b ? b->next : headA;                // 走完 B 换到 A
        }
        return a;
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

static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}

static ListNode* concat(ListNode* a, ListNode* b) {
    if (!a) return b;
    ListNode* t = a;
    while (t->next) t = t->next;
    t->next = b;
    return a;
}

int main() {
    struct Case {
        vector<int> a, b, common;                   // A 独有部分、B 独有部分、公共部分
    };
    vector<Case> cases = {
        {{4, 1}, {5, 6, 1}, {8, 4, 5}},
        {{1, 9, 1}, {3}, {2, 4}},
        {{2, 6, 4}, {1, 5}, {}},
        {{}, {7}, {3, 5}},
        {{1}, {}, {2}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        ListNode* common = build(c.common);
        ListNode* headA = concat(build(c.a), common);
        ListNode* headB = concat(build(c.b), common);
        ListNode* got = sol.getIntersectionNode(headA, headB);
        bool ok = got == common;                    // 必须是同一个节点，不只是值相等
        passed += ok;
        cout << "用例 " << k + 1 << ": A = ";
        printVec(c.a);
        cout << " + 公共 ";
        printVec(c.common);
        cout << ", B = ";
        printVec(c.b);
        cout << " + 公共";
        cout << "\n  输出: " << (got ? to_string(got->val) : "null")
             << "   期望: " << (common ? to_string(common->val) : "null");
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
