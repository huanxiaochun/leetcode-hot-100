/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 把两个数组各切一刀，左边一共 half 个数，并且左边的最大值 <= 右边的最小值
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) return findMedianSortedArrays(b, a);  // 在短的数组上二分
        int m = a.size(), n = b.size();
        int half = (m + n + 1) / 2;                 // 左半部分的个数（奇数时多放一个）
        int l = 0, r = m;                           // i = a 放进左半部分的个数，范围 [0, m]
        while (l <= r) {
            int i = (l + r) / 2, j = half - i;      // b 放进左半部分 j 个
            int aL = i > 0 ? a[i - 1] : INT_MIN;    // 切口左右的四个数，越界用无穷代替
            int aR = i < m ? a[i] : INT_MAX;
            int bL = j > 0 ? b[j - 1] : INT_MIN;
            int bR = j < n ? b[j] : INT_MAX;
            if (aL > bR) r = i - 1;                 // a 放多了
            else if (bL > aR) l = i + 1;            // a 放少了
            else {                                  // 切对了
                int leftMax = max(aL, bL);
                if ((m + n) % 2) return leftMax;
                return (leftMax + min(aR, bR)) / 2.0;
            }
        }
        return 0;                                   // 输入有序时不会走到这里
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
        vector<int> a, b;
        double expected;
    };
    vector<Case> cases = {
        {{1, 3}, {2}, 2.0},
        {{1, 2}, {3, 4}, 2.5},
        {{}, {1}, 1.0},
        {{2}, {}, 2.0},
        {{1, 3, 8, 9, 15}, {7, 11, 18, 19, 21, 25}, 11.0},
        {{-5, -3}, {-4, 10}, -3.5},
    };

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        double got = sol.findMedianSortedArrays(c.a, c.b);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums1 = ";
        printVec(c.a);
        cout << ", nums2 = ";
        printVec(c.b);
        cout << "\n  输出: " << got << "   期望: " << c.expected;
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == cases.size() ? 0 : 1;
}
