/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// 把所有数分成两半：lo 放较小的一半，hi 放较大的一半，并且 lo 比 hi 多 0 或 1 个
// 中位数只和两个堆顶有关
class MedianFinder {
    priority_queue<int> lo;                         // 大顶堆：堆顶是较小一半里最大的
    priority_queue<int, vector<int>, greater<int>> hi;  // 小顶堆：堆顶是较大一半里最小的

public:
    void addNum(int num) {
        lo.push(num);                               // ① 先放进较小的一半
        hi.push(lo.top());                          // ② 把较小一半里最大的挪过去，保证 lo 都 <= hi
        lo.pop();
        if (hi.size() > lo.size()) {                // ③ hi 多了就还一个回来
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() {
        if (lo.size() > hi.size()) return lo.top(); // 奇数个：中间那个在 lo 顶
        return (lo.top() + hi.top()) / 2.0;         // 偶数个：两个堆顶的平均
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

static void printDoubles(const vector<double>& v) {
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
        vector<double> expected;                    // 每次 findMedian 的返回值
    };
    vector<Case> cases = {
        {{{"add", 1}, {"add", 2}, {"find", 0}, {"add", 3}, {"find", 0}}, {1.5, 2.0}},
        {{{"add", 5}, {"find", 0}, {"add", 15}, {"find", 0}, {"add", 1}, {"find", 0}, {"add", 3}, {"find", 0}}, {5, 10, 5, 4}},
        {{{"add", -1}, {"find", 0}, {"add", -2}, {"find", 0}, {"add", -3}, {"find", 0}, {"add", -4}, {"find", 0}}, {-1, -1.5, -2, -2.5}},
        {{{"add", 6}, {"add", 10}, {"add", 2}, {"add", 6}, {"find", 0}, {"add", 5}, {"find", 0}}, {6, 6}},
    };

    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        MedianFinder mf;
        vector<double> got;
        cout << "用例 " << k + 1 << ": ";
        for (auto& op : c.ops) {
            if (op.name == "add") {
                mf.addNum(op.x);
                cout << "addNum(" << op.x << ") ";
            } else {
                got.push_back(mf.findMedian());
                cout << "findMedian() ";
            }
        }
        bool ok = got == c.expected;
        passed += ok;
        cout << "\n  findMedian 的结果: ";
        printDoubles(got);
        cout << "   期望: ";
        printDoubles(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
