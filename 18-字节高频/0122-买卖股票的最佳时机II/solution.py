"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        ans = 0
        for i in range(1, len(prices)):
            if prices[i] > prices[i - 1]:          # 涨就吃下
                ans += prices[i] - prices[i - 1]
        return ans


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
