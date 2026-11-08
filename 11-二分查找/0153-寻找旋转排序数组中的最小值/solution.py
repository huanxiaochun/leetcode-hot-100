"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def findMin(self, nums: List[int]) -> int:
        l, r = 0, len(nums) - 1
        while l < r:
            mid = (l + r) // 2
            if nums[mid] > nums[r]:                # mid 比最右边大：最小值在 mid 右边
                l = mid + 1
            else:                                  # [mid, r] 有序：最小值在 [l, mid]，mid 也可能是
                r = mid
        return nums[l]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [([3, 4, 5, 1, 2], 1), ([4, 5, 6, 7, 0, 1, 2], 0), ([11, 13, 15, 17], 11), ([2, 1], 1), ([1], 1)]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().findMin(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
