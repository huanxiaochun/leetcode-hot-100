/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        vector<int> d1 = walk(edges, node1), d2 = walk(edges, node2);
        int ans = -1, best = INT_MAX;
        for (int i = 0; i < (int)edges.size(); ++i) {
            if (d1[i] < 0 || d2[i] < 0) continue;            // 有一边到不了
            int d = max(d1[i], d2[i]);
            if (d < best) { best = d; ans = i; }             // 严格小于：平局留编号小的
        }
        return ans;
    }

private:
    // 从 start 沿唯一出边一直走，返回到每个点的距离，走不到的是 -1
    vector<int> walk(const vector<int>& edges, int start) {
        vector<int> d(edges.size(), -1);
        for (int x = start, step = 0; x != -1 && d[x] == -1; x = edges[x]) d[x] = step++;   // 走回走过的点就停（环）
        return d;
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
    struct Case { vector<int> edges; int node1, node2, expected; };
    vector<Case> cases = {
        {{2, 2, 3, -1}, 0, 1, 2},
        {{1, 2, -1}, 0, 2, 2},
        {{5, -1, 3, 4, 5, 6, -1, -1, 4, 3}, 0, 0, 0},   // 同一个点，距离 0
        {{1, 2, 0}, 0, 2, 0},                         // 环：0、1、2 的 max 分别是 1、2、2
        {{-1, -1}, 0, 1, -1},                         // 谁也到不了谁
        {{4, 4, 8, -1, 9, 8, 4, 4, 1, 1}, 5, 6, 1},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.closestMeetingNode(c.edges, c.node1, c.node2);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": edges = "; printVec(c.edges);
        cout << ", node1 = " << c.node1 << ", node2 = " << c.node2 << "\n  输出: " << got
             << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
