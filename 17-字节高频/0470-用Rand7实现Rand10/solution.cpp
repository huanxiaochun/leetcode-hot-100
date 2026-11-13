/*
 * 编译运行：
 *   g++ -std=c++17 -O2 solution.cpp -o /tmp/solution && /tmp/solution
 */
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// 力扣会提供 rand7()，本地用 mt19937 模拟
static mt19937 rng(2026);
static long long rand7Calls = 0;
int rand7() {
    ++rand7Calls;
    return uniform_int_distribution<int>(1, 7)(rng);
}

class Solution {
public:
    int rand10() {
        while (true) {
            int x = (rand7() - 1) * 7 + rand7();    // 均匀的 1~49
            if (x <= 40) return (x - 1) % 10 + 1;   // 1~40 均匀映射到 1~10
        }                                           // 41~49 丢掉重来
    }
};

// ============================================================
// ==                       本地测试                          ==
// ============================================================
// 随机算法没法比对固定输出，用两件事验证：值都在 1~10 内；每个值出现的频率接近 1/10
int main() {
    const int N = 1000000;
    Solution sol;
    vector<int> cnt(11, 0);
    bool inRange = true;
    for (int i = 0; i < N; ++i) {
        int v = sol.rand10();
        if (v < 1 || v > 10) { inRange = false; break; }
        ++cnt[v];
    }

    // 卡方检验：9 个自由度，显著性 0.001 的临界值约 27.88，均匀分布时统计量几乎不会超过它
    double expected = N / 10.0, chi2 = 0;
    for (int v = 1; v <= 10; ++v) chi2 += (cnt[v] - expected) * (cnt[v] - expected) / expected;
    double avgCalls = (double)rand7Calls / N;

    int passed = 0, total = 3;
    bool ok;
    ok = inRange; passed += ok;
    cout << "用例 1: 输出都在 1~10 内" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    ok = inRange && chi2 < 27.88; passed += ok;
    cout << "用例 2: 各值频率（" << N << " 次）：";
    for (int v = 1; v <= 10; ++v) cout << v << "=" << cnt[v] / (double)N << (v < 10 ? " " : "");
    cout << "\n  卡方 = " << chi2 << "（< 27.88 视为均匀）" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";
    ok = fabs(avgCalls - 2.45) < 0.05; passed += ok;
    cout << "用例 3: 平均每次调用 rand7 " << avgCalls << " 次（理论 2 × 49/40 = 2.45）" << "   " << (ok ? "\033[32m通过\033[0m" : "\033[31m失败\033[0m") << "\n\n";

    cout << passed << "/" << total << " 通过\n";
    return passed == total ? 0 : 1;
}
