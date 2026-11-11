/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> next(numCourses);       // next[b]：修完 b 之后才能修的课
        vector<int> indeg(numCourses, 0);           // 还差几门先修课
        for (auto& p : prerequisites) {             // [a, b]：先修 b 才能修 a，边 b -> a
            next[p[1]].push_back(p[0]);
            ++indeg[p[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
            if (indeg[i] == 0) q.push(i);           // 没有先修课的，现在就能修
        int done = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ++done;                                 // 修完 u
            for (int v : next[u])
                if (--indeg[v] == 0) q.push(v);     // v 的先修课全修完了
        }
        return done == numCourses;                  // 环上的课入度永远到不了 0
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================

int main() {
    struct Case {
        int n;
        vector<vector<int>> pre;
        bool expected;
    };
    vector<Case> cases = {
        {2, {{1, 0}}, true},
        {2, {{1, 0}, {0, 1}}, false},
        {4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}, true},
        {3, {{0, 1}, {1, 2}, {2, 0}}, false},
        {1, {}, true},
        {5, {{1, 0}, {2, 1}, {3, 2}, {1, 3}, {4, 0}}, false},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        bool got = sol.canFinish(c.n, c.pre);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": numCourses = " << c.n << ", prerequisites = [";
        for (size_t i = 0; i < c.pre.size(); ++i) cout << (i ? "," : "") << "[" << c.pre[i][0] << "," << c.pre[i][1] << "]";
        cout << "]\n  输出: " << boolalpha << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
