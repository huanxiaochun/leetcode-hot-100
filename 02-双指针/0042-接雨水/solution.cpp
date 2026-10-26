/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int lmax = 0, rmax = 0, water = 0;            // 左边、右边见过的最高柱子
        while (l < r) {
            lmax = max(lmax, height[l]);
            rmax = max(rmax, height[r]);
            if (lmax < rmax) {                        // 左边是短板，l 处水位就是 lmax
                water += lmax - height[l];
                ++l;
            } else {                                  // 右边是短板，r 处水位就是 rmax
                water += rmax - height[r];
                --r;
            }
        }
        return water;
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
        vector<int> height;
        int expected;
    };
    vector<Case> cases = {
        {{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}, 6},
        {{4, 2, 0, 3, 2, 5}, 9},
        {{1}, 0},
        {{3, 2, 1}, 0},
        {{5, 0, 0, 5}, 10},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.trap(c.height);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": height = ";
        printVec(c.height);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
