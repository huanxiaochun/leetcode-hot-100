"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n = len(prices)
        # dp[i][j]：第 i 天结束时处于状态 j 的最大收益
        # j = 0 没操作；j 奇数 = 第 (j + 1) // 2 次买入后；j 偶数 = 第 j // 2 次卖出后
        dp = [[0] * (2 * k + 1) for _ in range(n)]
        for j in range(1, 2 * k, 2):
            dp[0][j] = -prices[0]                  # 第 0 天买入
        for i in range(1, n):
            for j in range(1, 2 * k + 1):
                p = -prices[i] if j % 2 else prices[i]               # 奇数买、偶数卖
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] + p)   # 不动 / 从上一个状态走过来
        return dp[n - 1][2 * k]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (2, [2, 4, 1], 2),
        (2, [3, 2, 6, 5, 0, 3], 7),
        (1, [3, 2, 6, 5, 0, 3], 4),
        (3, [1, 4, 2, 7, 3, 9], 14),
        (2, [1], 0),
        (4, [1, 2, 4, 2, 5, 7, 2, 4, 9, 0], 15),
    ]
    passed = 0
    for t, (k, prices, expected) in enumerate(cases, 1):
        got = Solution().maxProfit(k, prices)
        ok = got == expected
        passed += ok
        print(f"用例 {t}: k = {k}, prices = {prices}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
