/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int iceBreakingGame(int num, int target) {
        int f = 0;                                  // 只剩 1 人时是 0 号
        for (int n = 2; n <= num; ++n) f = (f + target) % n;   // 从 n-1 人推到 n 人
        return f;
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
// 暴力模拟：真的一个个删，用来对拍
static int simulate(int num, int target) {
    vector<int> people(num);
    for (int i = 0; i < num; ++i) people[i] = i;
    int idx = 0;
    while (people.size() > 1) {
        idx = (idx + target - 1) % people.size();
        people.erase(people.begin() + idx);
    }
    return people[0];
}

int main() {
    struct Case { int num, target, expected; };
    vector<Case> cases = {
        {7, 4, 1},
        {12, 5, 0},
        {1, 1, 0},
        {5, 1, 4},        // 每次都是第一个离开，最后剩最后一个
        {100000, 1000000, -1},   // -1 表示只看能否快速跑完，和下面的公式自比
    };
    Solution sol;
    int passed = 0;
    for (size_t k = 0; k < cases.size(); ++k) {
        auto& c = cases[k];
        int got = sol.iceBreakingGame(c.num, c.target);
        bool ok = c.expected == -1 ? got >= 0 && got < c.num : got == c.expected;
        passed += ok;
        cout << "用例 " << k + 1 << ": num = " << c.num << ", target = " << c.target << "\n  输出: " << got;
        if (c.expected != -1) cout << "   期望: " << c.expected;
        else cout << "   （规模最大的情况，O(num) 秒出）";
        cout << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    }
    bool ok = true;
    for (int num = 1; num <= 40 && ok; ++num)
        for (int t = 1; t <= 40; ++t)
            if (sol.iceBreakingGame(num, t) != simulate(num, t)) { ok = false; break; }
    passed += ok;
    cout << "用例 " << cases.size() + 1 << ": 和暴力模拟对拍 num、target = 1~40" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";

    int total = cases.size() + 1;
    cout << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}
