/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;                              // 存下标，对应的值从队头到队尾单调递减
        vector<int> ans;
        for (int i = 0; i < nums.size(); ++i) {
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();                      // 比新来的小，以后不可能再是最大值
            dq.push_back(i);
            if (dq.front() <= i - k) dq.pop_front(); // 队头滑出窗口
            if (i >= k - 1) ans.push_back(nums[dq.front()]);  // 队头就是窗口最大值
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
        {{1, 3, -1, -3, 5, 3, 6, 7}, 3, {3, 3, 5, 5, 6, 7}},
        {{1}, 1, {1}},
        {{1, -1}, 1, {1, -1}},
        {{9, 8, 7, 6}, 2, {9, 8, 7}},
        {{4, 2, 12, 3}, 4, {12}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.maxSlidingWindow(c.nums, c.k);
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
