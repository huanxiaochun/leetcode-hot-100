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
    void moveZeroes(vector<int>& nums) {
        int j = 0;                                  // [0, j) 都是非零，保持原顺序
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                swap(nums[i], nums[j]);             // 非零换到前面，零被换到后面
                ++j;
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
        vector<int> nums;
        vector<int> expected;
    };
    vector<Case> cases = {
        {{0, 1, 0, 3, 12}, {1, 3, 12, 0, 0}},
        {{0}, {0}},
        {{1, 2, 3}, {1, 2, 3}},
        {{0, 0, 1}, {1, 0, 0}},
        {{4, 0, 5, 0, 0, 6}, {4, 5, 6, 0, 0, 0}},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        vector<int> got = c.nums;                   // 原地修改，拷贝一份保留输入
        sol.moveZeroes(got);
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
