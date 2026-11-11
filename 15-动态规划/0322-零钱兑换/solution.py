"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        # dp[i] = 凑出金额 i 最少要几枚硬币
        # amount + 1 枚不可能用到，当作「凑不出」
        dp = [0] + [amount + 1] * amount
        for i in range(1, amount + 1):
            for c in coins:                        # 最后一枚用面值 c
                if c <= i:
                    dp[i] = min(dp[i], dp[i - c] + 1)
        return -1 if dp[amount] > amount else dp[amount]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 5], 11, 3),
        ([2], 3, -1),
        ([1], 0, 0),
        ([2, 5, 10, 1], 27, 4),
        ([186, 419, 83, 408], 6249, 20),
        ([3, 7], 5, -1),
    ]
    passed = 0
    for k, (coins, amount, expected) in enumerate(cases, 1):
        got = Solution().coinChange(coins, amount)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: coins = {coins}, amount = {amount}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
