"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        dp = [0] * (amount + 1)
        dp[0] = 1                                         # 什么都不选也算一种
        for coin in coins:                                # 外层硬币 → 组合
            for j in range(coin, amount + 1):             # 金额从小到大 → 每种可无限用
                dp[j] += dp[j - coin]
        return dp[amount]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (5, [1, 2, 5], 4),     # 5 / 2+2+1 / 2+1+1+1 / 1×5
        (3, [2], 0),
        (10, [10], 1),
        (0, [7], 1),           # 什么都不选也算一种
        (4, [1, 2, 3], 4),
    ]
    passed = 0
    for k, (amount, coins, expected) in enumerate(cases, 1):
        got = Solution().change(amount, coins)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: amount = {amount}, coins = [{','.join(map(str, coins))}]")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
