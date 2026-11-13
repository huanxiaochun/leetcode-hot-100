/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size(), ans = INT_MAX;
        vector<long long> P(n + 1, 0);
        for (int i = 0; i < n; ++i) P[i + 1] = P[i] + nums[i];
        deque<int> dq;                                       // 存下标，P 单调递增
        for (int j = 0; j <= n; ++j) {
            while (!dq.empty() && P[j] - P[dq.front()] >= k) {   // 队头配上 j 够了
                ans = min(ans, j - dq.front());
                dq.pop_front();
            }
            while (!dq.empty() && P[dq.back()] >= P[j]) dq.pop_back();   // j 当起点更好
            dq.push_back(j);
        }
        return ans == INT_MAX ? -1 : ans;
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

static int brute(const vector<int>& a, int k) {
    int n = a.size(), ans = INT_MAX;
    for (int i = 0; i < n; ++i) {
        long long s = 0;
        for (int j = i; j < n; ++j) {
            s += a[j];
            if (s >= k) { ans = min(ans, j - i + 1); break; }
        }
    }
    return ans == INT_MAX ? -1 : ans;
}

int main() {
    struct Case { vector<int> nums; int k, expected; };
    vector<Case> cases = {
        {{1}, 1, 1},
        {{1, 2}, 4, -1},
        {{2, -1, 2}, 3, 3},
        {{84, -37, 32, 40, 95}, 167, 3},
        {{17, 85, 93, -45, -21}, 150, 2},
        {{-28, 81, -20, 28, -29}, 89, 3},
    };
    Solution sol;
    int passed = 0;
    for (size_t t = 0; t < cases.size(); ++t) {
        auto& c = cases[t];
        int got = sol.shortestSubarray(c.nums, c.k);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << t + 1 << ": nums = "; printVec(c.nums);
        cout << ", k = " << c.k << "\n  输出: " << got << "   期望: " << c.expected << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    mt19937 g(862);
    bool ok = true;
    for (int it = 0; it < 20000 && ok; ++it) {
        int n = g() % 12 + 1, k = g() % 30 + 1;
        vector<int> a(n);
        for (int& x : a) x = (int)(g() % 41) - 20;
        if (sol.shortestSubarray(a, k) != brute(a, k)) ok = false;
    }
    passed += ok;
    cout << "用例 " << cases.size() + 1 << ": 和暴力对拍 2 万组（含负数）" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";

    int total = cases.size() + 1;
    cout << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}
