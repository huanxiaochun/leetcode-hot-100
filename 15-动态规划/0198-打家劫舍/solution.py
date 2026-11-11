"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def rob(self, nums: List[int]) -> int:
        # dp[i] = 只看前 i 间房，最多偷多少
        # 第 i 间不偷：dp[i - 1]；偷：dp[i - 2] + nums[i]
        prev2, prev1 = 0, 0                        # dp[i - 2]、dp[i - 1]
        for x in nums:
            prev2, prev1 = prev1, max(prev1, prev2 + x)   # 往前滚一格
        return prev1


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 3, 1], 4),
        ([2, 7, 9, 3, 1], 12),
        ([5], 5),
        ([2, 1, 1, 2], 4),
        ([0, 0], 0),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().rob(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
