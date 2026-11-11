"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def canPartition(self, nums: List[int]) -> bool:
        total = sum(nums)
        if total % 2:                              # 总和是奇数，分不成两半
            return False
        target = total // 2
        # dp[j] = 用已经看过的数，能不能挑出几个凑成和 j
        dp = [True] + [False] * target             # dp[0]：一个都不挑，和是 0
        for x in nums:
            for j in range(target, x - 1, -1):     # 倒着走：每个数只能用一次
                if dp[j - x]:                      # 凑出 j - x 再加上 x
                    dp[j] = True
        return dp[target]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 5, 11, 5], True),
        ([1, 2, 3, 5], False),
        ([1, 1], True),
        ([2, 2, 3, 5], False),
        ([3, 3, 3, 4, 5], True),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().canPartition(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
