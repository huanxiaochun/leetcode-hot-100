/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }

private:
    mt19937 rng{random_device{}()};

    void quickSort(vector<int>& a, int l, int r) {
        if (l >= r) return;
        int pivot = a[uniform_int_distribution<int>(l, r)(rng)];   // 随机基准
        int lt = l, i = l, gt = r;
        while (i <= gt) {
            if (a[i] < pivot) swap(a[i++], a[lt++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);              // i 不动：换来的数还没看
            else ++i;
        }
        quickSort(a, l, lt - 1);                                     // < pivot
        quickSort(a, gt + 1, r);                                     // > pivot
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
    vector<vector<int>> cases = {
        {5, 2, 3, 1},
        {5, 1, 1, 2, 0, 0},
        {1},
        {},
        {2, 2, 2, 2, 2, 2},
        {-1, 3, -5, 0, 3, -1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
    };
    // 再加一组大数据：5 万个数、只有 3 种值，二路划分会很慢，三路划分很快
    mt19937 g(42);
    vector<int> big(50000);
    for (int& x : big) x = g() % 3;
    cases.push_back(big);

    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto expected = cases[k];
        sort(expected.begin(), expected.end());
        auto in = cases[k];
        auto got = sol.sortArray(in);
        bool ok = got == expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": ";
        if (cases[k].size() <= 20) {
            cout << "nums = "; printVec(cases[k]);
            cout << "\n  输出: "; printVec(got);
        } else {
            cout << "n = " << cases[k].size() << "（只有 0/1/2 三种值）\n  输出与 std::sort 一致";
        }
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    cout << passed << "/" << cases.size() << " 通过\n";
    return passed == (int)cases.size() ? 0 : 1;
}
