/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class MyQueue {
public:
    void push(int x) { in.push(x); }

    int pop() {
        int x = peek();                             // peek 会保证 out 栈顶是队头
        out.pop();
        return x;
    }

    int peek() {
        if (out.empty())                            // out 空了才倒
            while (!in.empty()) { out.push(in.top()); in.pop(); }
        return out.top();
    }

    bool empty() { return in.empty() && out.empty(); }

private:
    stack<int> in, out;
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
// 操作序列：push 带参数；pop/peek 期望返回值；empty 期望 0/1
int main() {
    struct Op { string name; int arg; };
    struct Case { vector<Op> ops; vector<int> expected; };   // expected 只记有返回值的操作
    vector<Case> cases = {
        {{{"push", 1}, {"push", 2}, {"peek", 0}, {"pop", 0}, {"empty", 0}}, {1, 1, 0}},
        {{{"push", 1}, {"push", 2}, {"pop", 0}, {"push", 3}, {"pop", 0}, {"pop", 0}, {"empty", 0}}, {1, 2, 3, 1}},
        {{{"empty", 0}, {"push", 5}, {"empty", 0}, {"peek", 0}, {"pop", 0}, {"empty", 0}}, {1, 0, 5, 5, 1}},
        // out 里还有元素时再 push，不能倒：先出 2，再出 3、4
        {{{"push", 1}, {"push", 2}, {"pop", 0}, {"push", 3}, {"push", 4}, {"peek", 0}, {"pop", 0}, {"pop", 0}, {"pop", 0}},
         {1, 2, 2, 3, 4}},
    };
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        MyQueue q;
        vector<int> got;
        cout << "用例 " << k + 1 << ": ";
        for (size_t t = 0; t < c.ops.size(); ++t) {
            auto& op = c.ops[t];
            cout << (t ? ", " : "") << op.name;
            if (op.name == "push") { cout << "(" << op.arg << ")"; q.push(op.arg); }
            else if (op.name == "pop") got.push_back(q.pop());
            else if (op.name == "peek") got.push_back(q.peek());
            else got.push_back(q.empty());
        }
        bool ok = got == c.expected;
        passed += ok;
        cout << "\n  返回: [";
        for (size_t t = 0; t < got.size(); ++t) cout << (t ? "," : "") << got[t];
        cout << "]   期望: [";
        for (size_t t = 0; t < c.expected.size(); ++t) cout << (t ? "," : "") << c.expected[t];
        cout << "]" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
