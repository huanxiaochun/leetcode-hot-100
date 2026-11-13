"""
运行：
    python3 solution.py
"""
from math import inf
from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        min_price, ans = inf, 0
        for p in prices:
            min_price = min(min_price, p)          # 之前（含今天）的最低价
            ans = max(ans, p - min_price)          # 今天卖能赚多少
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([7, 1, 5, 3, 6, 4], 5),
        ([7, 6, 4, 3, 1], 0),
        ([1], 0),
        ([2, 4, 1], 2),                            # 最低价 1 在最后，买不了
        ([3, 2, 6, 5, 0, 3], 4),
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
