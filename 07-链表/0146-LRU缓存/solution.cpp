/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// 哈希表 O(1) 找到节点，双向链表 O(1) 挪动和删除
// 链表顺序：head 后面最久没用，tail 前面最近用过
class LRUCache {
    struct Node {
        int key, val;
        Node *prev = nullptr, *next = nullptr;
        Node(int k = 0, int v = 0) : key(k), val(v) {}
    };
    int cap;
    unordered_map<int, Node*> pos;                  // key -> 链表里的节点
    Node head, tail;                                // 哨兵，省掉判空

    void unlink(Node* x) {                          // 从链表里摘下来
        x->prev->next = x->next;
        x->next->prev = x->prev;
    }
    void pushBack(Node* x) {                        // 放到 tail 前面，表示最近用过
        x->prev = tail.prev;
        x->next = &tail;
        tail.prev->next = x;
        tail.prev = x;
    }

public:
    LRUCache(int capacity) : cap(capacity) {
        head.next = &tail;
        tail.prev = &head;
    }
    ~LRUCache() {
        for (auto& [k, x] : pos) delete x;
    }
    LRUCache(const LRUCache&) = delete;             // 节点归这个对象管，禁止拷贝
    LRUCache& operator=(const LRUCache&) = delete;

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;
        Node* x = it->second;
        unlink(x);                                  // 用过了，挪到最后
        pushBack(x);
        return x->val;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {                      // 已存在：改值，挪到最后
            it->second->val = value;
            unlink(it->second);
            pushBack(it->second);
            return;
        }
        if (pos.size() == cap) {                    // 满了：删最久没用的
            Node* old = head.next;
            unlink(old);
            pos.erase(old->key);
            delete old;
        }
        Node* x = new Node(key, value);
        pushBack(x);
        pos[key] = x;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << v[i];
    cout << "]";
}

int main() {
    struct Op {
        string name;
        int a, b;
    };
    struct Case {
        int capacity;
        vector<Op> ops;
        vector<int> expected;                       // 每次 get 的返回值
    };
    vector<Case> cases = {
        {2, {{"put", 1, 1}, {"put", 2, 2}, {"get", 1, 0}, {"put", 3, 3}, {"get", 2, 0},
             {"put", 4, 4}, {"get", 1, 0}, {"get", 3, 0}, {"get", 4, 0}}, {1, -1, -1, 3, 4}},
        {1, {{"put", 2, 1}, {"get", 2, 0}, {"put", 3, 2}, {"get", 2, 0}, {"get", 3, 0}}, {1, -1, 2}},
        {2, {{"put", 1, 1}, {"put", 2, 2}, {"put", 1, 10}, {"put", 3, 3}, {"get", 1, 0}, {"get", 2, 0}}, {10, -1}},
        {2, {{"get", 1, 0}, {"put", 1, 5}, {"get", 1, 0}}, {-1, 5}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        LRUCache cache(c.capacity);
        vector<int> got;
        cout << "用例 " << k + 1 << ": capacity = " << c.capacity << ", ";
        for (auto& op : c.ops) {
            if (op.name == "put") {
                cache.put(op.a, op.b);
                cout << "put(" << op.a << "," << op.b << ") ";
            } else {
                got.push_back(cache.get(op.a));
                cout << "get(" << op.a << ") ";
            }
        }
        bool ok = got == c.expected;
        passed += ok;
        cout << "\n  get 的结果: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
