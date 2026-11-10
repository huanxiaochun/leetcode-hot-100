/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// 再开一个栈 mn，和 st 一起压、一起弹：mn 的栈顶就是 st 里当前的最小值
class MinStack {
    stack<int> st, mn;

public:
    MinStack() { mn.push(INT_MAX); }                // 哨兵：省掉 push 时判空

    void push(int val) {
        st.push(val);
        mn.push(min(val, mn.top()));                // 到这一层为止的最小值
    }

    void pop() {
        st.pop();
        mn.pop();                                   // 弹掉后，mn 栈顶自动回到之前的最小值
    }

    int top() { return st.top(); }

    int getMin() { return mn.top(); }
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
        int x;
    };
    struct Case {
        vector<Op> ops;
        vector<int> expected;                       // 每次 top / getMin 的返回值
    };
    vector<Case> cases = {
        {{{"push", -2}, {"push", 0}, {"push", -3}, {"getMin", 0}, {"pop", 0}, {"top", 0}, {"getMin", 0}}, {-3, 0, -2}},
        {{{"push", 1}, {"push", 1}, {"push", 2}, {"getMin", 0}, {"pop", 0}, {"getMin", 0}, {"pop", 0}, {"getMin", 0}}, {1, 1, 1}},
        {{{"push", 5}, {"getMin", 0}, {"push", 3}, {"getMin", 0}, {"push", 7}, {"getMin", 0},
          {"pop", 0}, {"pop", 0}, {"getMin", 0}, {"top", 0}}, {5, 3, 3, 5, 5}},
        {{{"push", INT_MAX}, {"getMin", 0}, {"push", INT_MIN}, {"getMin", 0}, {"pop", 0}, {"getMin", 0}},
         {INT_MAX, INT_MIN, INT_MAX}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        MinStack ms;
        vector<int> got;
        cout << "用例 " << k + 1 << ": ";
        for (auto& op : c.ops) {
            if (op.name == "push") {
                ms.push(op.x);
                cout << "push(" << op.x << ") ";
            } else if (op.name == "pop") {
                ms.pop();
                cout << "pop() ";
            } else if (op.name == "top") {
                got.push_back(ms.top());
                cout << "top() ";
            } else {
                got.push_back(ms.getMin());
                cout << "getMin() ";
            }
        }
        bool ok = got == c.expected;
        passed += ok;
        cout << "\n  top / getMin 的结果: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
