"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def findPeakElement(self, nums: List[int]) -> int:
        lo, hi = 0, len(nums) - 1
        while lo < hi:
            mid = (lo + hi) // 2
            if nums[mid] < nums[mid + 1]:          # 右边是上坡，峰在右边
                lo = mid + 1
            else:                                  # mid 可能就是峰
                hi = mid
        return lo


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def is_peak(a, i):
    """答案不唯一，只要是峰就算对"""
    n = len(a)
    if i < 0 or i >= n:
        return False
    return (i == 0 or a[i] > a[i - 1]) and (i == n - 1 or a[i] > a[i + 1])


if __name__ == "__main__":
    cases = [
        [1, 2, 3, 1],
        [1, 2, 1, 3, 5, 6, 4],
        [1],
        [1, 2],
        [2, 1],
        [5, 4, 3, 2, 1],
        [1, 2, 3, 4, 5],
    ]
    passed = 0
    for k, nums in enumerate(cases, 1):
        got = Solution().findPeakElement(nums)
        ok = is_peak(nums, got)
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   （nums[{got}] 是峰）   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
