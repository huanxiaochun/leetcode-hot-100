/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l = 0, r = nums.size();                 // 答案在左闭右开区间 [l, r) 里
        while (l < r) {
            int mid = l + (r - l) / 2;              // 不写 (l + r) / 2，避免 l + r 溢出
            if (nums[mid] < target) l = mid + 1;    // mid 太小，答案在右边
            else r = mid;                           // nums[mid] >= target，mid 可能就是答案
        }
        return l;                                   // 第一个 >= target 的位置
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
        int target;
        int expected;
    };
    vector<Case> cases = {
        {{1, 3, 5, 6}, 5, 2},
        {{1, 3, 5, 6}, 2, 1},
        {{1, 3, 5, 6}, 7, 4},
        {{1, 3, 5, 6}, 0, 0},
        {{1}, 1, 0},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = sol.searchInsert(c.nums, c.target);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(c.nums);
        cout << ", target = " << c.target;
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
