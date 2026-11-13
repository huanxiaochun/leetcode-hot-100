/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

// 把 i -> nums[i] 看成链表的 next：值都在 [1, n]，从 0 出发一定会走进环
// 重复的数有两个下标指向它，它就是环的入口
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];                      // 慢指针走 1 步
            fast = nums[nums[fast]];                // 快指针走 2 步
        } while (slow != fast);                     // 第一阶段：在环里相遇
        slow = 0;                                   // 一个回到起点
        while (slow != fast) {                      // 第二阶段：同速走，在环的入口相遇
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
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
        {{1, 3, 4, 2, 2}, 2},
        {{3, 1, 3, 4, 2}, 3},
        {{3, 3, 3, 3, 3}, 3},
        {{1, 1}, 1},
        {{2, 2, 2}, 2},
        {{1, 4, 4, 2, 4}, 4},
        {{2, 5, 9, 6, 9, 3, 8, 9, 7, 1}, 9},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.findDuplicate(c.nums);
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
