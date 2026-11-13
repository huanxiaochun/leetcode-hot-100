/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        // [0, lo) 全是 0，[lo, i) 全是 1，(hi, n) 全是 2，[i, hi] 还没看
        int lo = 0, i = 0, hi = nums.size() - 1;
        while (i <= hi) {
            if (nums[i] == 0) {
                swap(nums[i++], nums[lo++]);        // 换来的是 1（或它自己），i 可以前进
            } else if (nums[i] == 2) {
                swap(nums[i], nums[hi--]);          // 换过来的数还没看过，i 不动
            } else {
                ++i;                                // 1 就留在中间
            }
        }
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
        vector<int> nums, expected;
    };
    vector<Case> cases = {
        {{2, 0, 2, 1, 1, 0}, {0, 0, 1, 1, 2, 2}},
        {{2, 0, 1}, {0, 1, 2}},
        {{0}, {0}},
        {{2, 2, 2}, {2, 2, 2}},
        {{1, 0}, {0, 1}},
        {{2, 1, 0, 2, 0, 1, 2}, {0, 0, 1, 1, 2, 2, 2}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = c.nums;                          // 原地修改，拷贝一份保留输入
        sol.sortColors(got);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << "\n  输出: ";
        printVec(got);
        cout << "   期望: ";
        printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
