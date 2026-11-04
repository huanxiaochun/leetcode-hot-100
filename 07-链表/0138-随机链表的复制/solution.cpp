/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <utility>

using namespace std;

// LeetCode 已经定义好节点，本地运行需要自己写一份
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        for (Node* p = head; p; p = p->next->next) {    // ① 每个节点后面插一个复制：A A' B B' ...
            Node* c = new Node(p->val);
            c->next = p->next;
            p->next = c;
        }
        for (Node* p = head; p; p = p->next->next)      // ② 复制的 random = 原 random 的复制
            if (p->random) p->next->random = p->random->next;
        Node* copyHead = head->next;
        for (Node* p = head; p; p = p->next) {          // ③ 拆成两条链，原链表恢复原样
            Node* c = p->next;
            p->next = c->next;
            c->next = c->next ? c->next->next : nullptr;
        }
        return copyHead;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
// 每个节点用 {val, random 的下标} 表示，-1 表示 random 为 null
using Spec = vector<pair<int, int>>;

static vector<Node*> buildRandom(const Spec& spec) {
    vector<Node*> nodes;
    for (auto& [v, r] : spec) nodes.push_back(new Node(v));
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i + 1 < nodes.size()) nodes[i]->next = nodes[i + 1];
        if (spec[i].second >= 0) nodes[i]->random = nodes[spec[i].second];
    }
    return nodes;
}

static Spec toSpec(Node* head) {
    vector<Node*> nodes;
    for (Node* p = head; p; p = p->next) nodes.push_back(p);
    Spec spec;
    for (Node* p : nodes) {
        int r = -1;
        for (size_t i = 0; i < nodes.size(); ++i)
            if (nodes[i] == p->random) r = i;
        spec.push_back({p->val, r});
    }
    return spec;
}

static void printSpec(const Spec& s) {
    cout << "[";
    for (size_t i = 0; i < s.size(); ++i)
        cout << (i ? "," : "") << "[" << s[i].first << "," << (s[i].second < 0 ? "null" : to_string(s[i].second)) << "]";
    cout << "]";
}

int main() {
    struct Case {
        Spec list;
    };
    vector<Case> cases = {
        {{{7, -1}, {13, 0}, {11, 4}, {10, 2}, {1, 0}}},
        {{{1, 1}, {2, 1}}},
        {{{3, -1}, {3, 0}, {3, -1}}},
        {{}},
        {{{5, 0}}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto nodes = buildRandom(c.list);
        Node* head = nodes.empty() ? nullptr : nodes[0];
        Node* copy = sol.copyRandomList(head);
        Spec got = toSpec(copy);
        unordered_set<Node*> orig(nodes.begin(), nodes.end());
        bool deep = true;                           // 复制出来的节点不能和原节点是同一个
        for (Node* p = copy; p; p = p->next)
            if (orig.count(p)) deep = false;
        bool ok = got == c.list && deep && toSpec(head) == c.list;  // 原链表也要恢复
        passed += ok;
        cout << "用例 " << k + 1 << ": head = ";
        printSpec(c.list);
        cout << "\n  输出: ";
        printSpec(got);
        cout << (deep ? "（全新节点）" : "（用了原节点！）");
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
