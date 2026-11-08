"""
运行：
    python3 solution.py
"""
from typing import List

class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        l, r = 0, len(nums)                        # 答案在左闭右开区间 [l, r) 里
        while l < r:
            mid = (l + r) // 2                     # Python 整数不会溢出
            if nums[mid] < target:                 # mid 太小，答案在右边
                l = mid + 1
            else:                                  # nums[mid] >= target，mid 可能就是答案
                r = mid
        return l                                   # 第一个 >= target 的位置


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 3, 5, 6], 5, 2),
        ([1, 3, 5, 6], 2, 1),
        ([1, 3, 5, 6], 7, 4),
        ([1, 3, 5, 6], 0, 0),
        ([1], 1, 0),
    ]
    passed = 0
    for k, (nums, target, expected) in enumerate(cases, 1):
        got = Solution().searchInsert(nums, target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}, target = {target}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
