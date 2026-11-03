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
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            // 把 x 放到下标 x-1 上；目标位置已经是 x 就停，避免死循环
            while (nums[i] >= 1 && nums[i] <= n && nums[nums[i] - 1] != nums[i])
                swap(nums[i], nums[nums[i] - 1]);
        }
        for (int i = 0; i < n; ++i)
            if (nums[i] != i + 1) return i + 1;     // 第一个没归位的位置
        return n + 1;                               // 1..n 都在
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
        {{1, 2, 0}, 3},
        {{3, 4, -1, 1}, 2},
        {{7, 8, 9, 11, 12}, 1},
        {{1, 1}, 2},
        {{2, 1}, 3},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        vector<int> input = c.nums;                 // 原地交换，留一份用来打印
        int got = sol.firstMissingPositive(c.nums);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums = ";
        printVec(input);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
