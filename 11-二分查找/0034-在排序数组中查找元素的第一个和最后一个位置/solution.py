"""
运行：
    python3 solution.py
"""
from typing import List

class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        def lower_bound(t):                        # 第一个 >= t 的位置
            l, r = 0, len(nums)
            while l < r:
                mid = (l + r) // 2
                if nums[mid] < t:
                    l = mid + 1
                else:
                    r = mid
            return l

        first = lower_bound(target)
        if first == len(nums) or nums[first] != target:
            return [-1, -1]
        return [first, lower_bound(target + 1) - 1]   # 第一个 > target 的前一个


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([5, 7, 7, 8, 8, 10], 8, [3, 4]),
        ([5, 7, 7, 8, 8, 10], 6, [-1, -1]),
        ([], 0, [-1, -1]),
        ([1], 1, [0, 0]),
        ([2, 2, 2], 2, [0, 2]),
    ]
    passed = 0
    for k, (nums, target, expected) in enumerate(cases, 1):
        got = Solution().searchRange(nums, target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}, target = {target}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
