"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        n = len(nums)
        # mx[i] / mn[i] = 以 nums[i] 结尾的子数组，乘积最大 / 最小是多少
        # 要记最小：乘上一个负数，最小的会变成最大的
        mx, mn = [0] * n, [0] * n
        mx[0] = mn[0] = nums[0]                    # 以第一个数结尾的只有它自己
        ans = nums[0]
        for i in range(1, n):
            x = nums[i]
            a, b = mx[i - 1] * x, mn[i - 1] * x    # 接在以 nums[i - 1] 结尾的那段后面
            mx[i] = max(x, a, b)                   # 或者从 x 自己重新开始
            mn[i] = min(x, a, b)
            ans = max(ans, mx[i])
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 3, -2, 4], 6),
        ([-2, 0, -1], 0),
        ([-2, 3, -4], 24),
        ([-2], -2),
        ([0, 2], 2),
        ([2, -5, -2, -4, 3], 24),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().maxProduct(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
