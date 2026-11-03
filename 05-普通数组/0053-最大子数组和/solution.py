"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        cur = best = nums[0]                       # cur：以当前元素结尾的最大和
        for x in nums[1:]:
            cur = max(x, cur + x)                  # 前面的和是负数就丢掉，从自己重新开始
            best = max(best, cur)
        return best


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([-2, 1, -3, 4, -1, 2, 1, -5, 4], 6),
        ([1], 1),
        ([5, 4, -1, 7, 8], 23),
        ([-3, -1, -2], -1),
        ([2, -1, 2, -10, 3], 3),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().maxSubArray(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
