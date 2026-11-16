"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        # dp[i][j]：第 i 天结束时处于状态 j 的最大收益
        # 0 没操作，1 第一次买入后，2 第一次卖出后，3 第二次买入后，4 第二次卖出后
        dp = [[0] * 5 for _ in range(n)]
        dp[0][1] = dp[0][3] = -prices[0]           # 第 0 天买入（买 → 卖 → 再买）
        for i in range(1, n):
            p = prices[i]
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p)   # 不动 / 第一次买
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + p)   # 不动 / 第一次卖
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - p)   # 不动 / 第二次买
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + p)   # 不动 / 第二次卖
        return dp[n - 1][4]                        # 只交易一次也包含在里面


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([3, 3, 5, 0, 0, 3, 1, 4], 6),
        ([1, 2, 3, 4, 5], 4),
        ([7, 6, 4, 3, 1], 0),
        ([1], 0),
        ([1, 4, 2, 7, 3, 9], 12),
        ([2, 1, 4, 5, 2, 9, 7], 11),
    ]
    passed = 0
    for k, (prices, expected) in enumerate(cases, 1):
        got = Solution().maxProfit(prices)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: prices = {prices}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
