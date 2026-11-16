"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [[0, 0] for _ in range(n)]            # dp[i][0] 不持有，dp[i][1] 持有
        dp[0][1] = -prices[0]                      # 第 0 天买入
        for i in range(1, n):
            p = prices[i]
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + p)   # 不动 / 今天卖
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - p)   # 不动 / 今天买
        return dp[n - 1][0]                        # 最后手里没股票


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([7, 1, 5, 3, 6, 4], 7),
        ([1, 2, 3, 4, 5], 4),
        ([7, 6, 4, 3, 1], 0),
        ([1], 0),
        ([2, 1, 2, 0, 1], 2),
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
