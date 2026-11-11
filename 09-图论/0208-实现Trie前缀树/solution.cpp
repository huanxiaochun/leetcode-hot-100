/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// 每个结点有 26 个孩子，对应 a ~ z；从根往下走一条路就拼出一个前缀
class Trie {
    struct Node {
        array<unique_ptr<Node>, 26> child;          // unique_ptr：Trie 析构时自动释放整棵树
        bool isEnd = false;                         // 有单词正好在这里结束
    };
    Node root;

    // 沿着 s 往下走，走不通返回 nullptr
    const Node* walk(const string& s) const {
        const Node* p = &root;
        for (char c : s) {
            p = p->child[c - 'a'].get();
            if (!p) return nullptr;
        }
        return p;
    }

public:
    void insert(string word) {
        Node* p = &root;
        for (char c : word) {
            auto& nx = p->child[c - 'a'];
            if (!nx) nx = make_unique<Node>();      // 没有这条路就新建
            p = nx.get();
        }
        p->isEnd = true;
    }

    bool search(string word) {
        const Node* p = walk(word);
        return p && p->isEnd;                       // 走得通，还得有单词在这里结束
    }

    bool startsWith(string prefix) {
        return walk(prefix) != nullptr;             // 走得通就行
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

static void printBools(const vector<bool>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) cout << (i ? "," : "") << (v[i] ? "true" : "false");
    cout << "]";
}

int main() {
    struct Op {
        string name, s;
    };
    struct Case {
        vector<Op> ops;
        vector<bool> expected;                      // 每次 search / startsWith 的返回值
    };
    vector<Case> cases = {
        {{{"insert", "apple"}, {"search", "apple"}, {"search", "app"}, {"startsWith", "app"},
          {"insert", "app"}, {"search", "app"}}, {true, false, true, true}},
        {{{"insert", "a"}, {"search", "a"}, {"startsWith", "a"}, {"search", "b"}}, {true, true, false}},
        {{{"insert", "car"}, {"insert", "cat"}, {"startsWith", "ca"}, {"search", "ca"}, {"search", "cat"},
          {"startsWith", "cb"}, {"search", "cart"}}, {true, false, true, false, false}},
        {{{"startsWith", "x"}, {"insert", "xyz"}, {"startsWith", "xyz"}, {"search", "xy"}}, {false, true, false}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        Trie t;
        vector<bool> got;
        cout << "用例 " << k + 1 << ": ";
        for (auto& op : c.ops) {
            if (op.name == "insert") t.insert(op.s);
            else if (op.name == "search") got.push_back(t.search(op.s));
            else got.push_back(t.startsWith(op.s));
            cout << op.name << "(\"" << op.s << "\") ";
        }
        bool ok = got == c.expected;
        passed += ok;
        cout << "\n  search / startsWith 的结果: ";
        printBools(got);
        cout << "   期望: ";
        printBools(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
