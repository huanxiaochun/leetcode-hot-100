"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        n = len(nums)
        for i in range(n):
            # 把 x 放到下标 x-1 上；目标位置已经是 x 就停，避免死循环
            while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:
                j = nums[i] - 1                    # 先算好目标下标再交换
                nums[i], nums[j] = nums[j], nums[i]
        for i in range(n):
            if nums[i] != i + 1:                   # 第一个没归位的位置
                return i + 1
        return n + 1                               # 1..n 都在


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 0], 3),
        ([3, 4, -1, 1], 2),
        ([7, 8, 9, 11, 12], 1),
        ([1, 1], 2),
        ([2, 1], 3),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().firstMissingPositive(nums[:])  # 原地交换，传副本
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
