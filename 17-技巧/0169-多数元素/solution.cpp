/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int cand = 0, cnt = 0;                      // 擂台上的候选人、他的票数
        for (int x : nums) {
            if (cnt == 0) cand = x;                 // 擂台空了，x 上台
            cnt += x == cand ? 1 : -1;              // 相同加一票，不同就互相抵消一票
        }
        return cand;                                // 多数元素比其余加起来还多，最后留下的一定是它
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
        int expected;
    };
    vector<Case> cases = {
        {{3, 2, 3}, 3},
        {{2, 2, 1, 1, 1, 2, 2}, 2},
        {{1}, 1},
        {{6, 5, 5}, 5},
        {{1, 2, 3, 4, 4, 4, 4}, 4},
        {{-1, -1, 7}, -1},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.majorityElement(c.nums);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
