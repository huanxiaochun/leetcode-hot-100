/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> h(heights);
        h.insert(h.begin(), 0);                     // 两头各放一根高度 0 的哨兵：
        h.push_back(0);                             // 左边的永远不会弹出，右边的会把栈清空
        stack<int> st;                              // 存下标，高度从栈底到栈顶递增
        int best = 0;
        for (int i = 0; i < h.size(); ++i) {
            while (!st.empty() && h[st.top()] > h[i]) {
                int height = h[st.top()];           // 以这根柱子的高度为矩形的高
                st.pop();
                int left = st.top();                // 左边第一根比它矮的
                best = max(best, height * (i - left - 1));   // 右边第一根比它矮的是 i，宽度是 (left, i) 之间
            }
            st.push(i);
        }
        return best;
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
    struct Case {
        vector<int> heights;
        int expected;
    };
    vector<Case> cases = {
        {{2, 1, 5, 6, 2, 3}, 10},
        {{2, 4}, 4},
        {{1}, 1},
        {{2, 2, 2}, 6},
        {{5, 4, 1, 2}, 8},
        {{0}, 0},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.largestRectangleArea(c.heights);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": heights = ";
        printVec(c.heights);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
