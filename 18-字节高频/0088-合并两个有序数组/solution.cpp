/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (j >= 0) {                            // nums2 放完就结束
            if (i >= 0 && nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
            else nums1[k--] = nums2[j--];
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
    struct Case { vector<int> nums1; int m; vector<int> nums2; int n; vector<int> expected; };
    vector<Case> cases = {
        {{1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}, 3, {1, 2, 2, 3, 5, 6}},
        {{1}, 1, {}, 0, {1}},
        {{0}, 0, {1}, 1, {1}},
        {{4, 5, 6, 0, 0, 0}, 3, {1, 2, 3}, 3, {1, 2, 3, 4, 5, 6}},
        {{1, 2, 3, 0, 0, 0}, 3, {4, 5, 6}, 3, {1, 2, 3, 4, 5, 6}},
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        auto got = c.nums1;
        sol.merge(got, c.m, c.nums2, c.n);
        bool ok = got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": nums1 = "; printVec(c.nums1);
        cout << ", m = " << c.m << ", nums2 = "; printVec(c.nums2);
        cout << ", n = " << c.n << "\n  输出: "; printVec(got);
        cout << "   期望: "; printVec(c.expected);
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
