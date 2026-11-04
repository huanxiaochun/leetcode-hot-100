/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>
#include <queue>

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };  // 小顶堆
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for (ListNode* h : lists)
            if (h) pq.push(h);                      // 每条链的头先进堆
        ListNode dummy;
        ListNode* tail = &dummy;
        while (!pq.empty()) {
            ListNode* x = pq.top();                 // 当前所有链头里最小的
            pq.pop();
            tail = tail->next = x;
            if (x->next) pq.push(x->next);          // 补上它所在链的下一个
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
static void printVecs(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) cout << ",";
        printVec(v[i]);
    }
    cout << "]";
}

int main() {
    struct Case {
        vector<vector<int>> lists;
        vector<int> expected;
    };
    vector<Case> cases = {
        {{{1, 4, 5}, {1, 3, 4}, {2, 6}}, {1, 1, 2, 3, 4, 4, 5, 6}},
        {{}, {}},
        {{{}}, {}},
        {{{2}, {}, {1}}, {1, 2}},
        {{{1, 2, 3}}, {1, 2, 3}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        vector<ListNode*> heads;
        for (auto& v : c.lists) heads.push_back(build(v));
        auto got = toVec(sol.mergeKLists(heads));
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": lists = ";
        printVecs(c.lists);
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
