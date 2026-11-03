"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        ans = [1] * n
        for i in range(1, n):
            ans[i] = ans[i - 1] * nums[i - 1]      # 先存左边所有数的乘积
        right = 1                                  # 右边所有数的乘积
        for i in range(n - 1, -1, -1):
            ans[i] *= right                        # 左积 × 右积
            right *= nums[i]
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 3, 4], [24, 12, 8, 6]),
        ([-1, 1, 0, -3, 3], [0, 0, 9, 0, 0]),
        ([2, 3], [3, 2]),
        ([0, 0, 5], [0, 0, 0]),
        ([1, -1, 2, -2], [4, -4, 2, -2]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().productExceptSelf(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
