/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> cnt;
        for (int x : nums) cnt[x]++;                // 先数每个数出现几次
        using P = pair<int, int>;                   // {次数, 数}：pair 先比 first，按次数排
        priority_queue<P, vector<P>, greater<P>> pq;   // 小顶堆：只留次数最多的 k 个
        for (auto& [x, c] : cnt) {
            pq.push({c, x});
            if (pq.size() > k) pq.pop();            // 超过 k 个，扔掉次数最少的
        }
        vector<int> ans;
        while (!pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
        }
        return ans;
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
        vector<int> nums;
        int k;
        vector<int> expected;
    };
    vector<Case> cases = {
        {{1, 1, 1, 2, 2, 3}, 2, {1, 2}},
        {{1}, 1, {1}},
        {{4, 1, -1, 2, -1, 2, 3}, 2, {-1, 2}},
        {{5, 5, 6, 6, 6, 7}, 1, {6}},
        {{1, 2}, 2, {1, 2}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.topKFrequent(c.nums, c.k);
        sort(got.begin(), got.end());               // 题目允许任意顺序
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << ", k = " << c.k << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
