"""
运行：
    python3 solution.py
"""
from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        l, r = 0, len(nums) - 1                    # 闭区间 [l, r]
        while l <= r:
            mid = (l + r) // 2
            if nums[mid] == target:
                return mid
            if nums[l] <= nums[mid]:               # 左半段 [l, mid] 有序（等号：l == mid 时只有一个数）
                if nums[l] <= target < nums[mid]:  # target 落在有序的左半段
                    r = mid - 1
                else:
                    l = mid + 1
            else:                                  # 右半段 [mid, r] 有序
                if nums[mid] < target <= nums[r]:  # target 落在有序的右半段
                    l = mid + 1
                else:
                    r = mid - 1
        return -1


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([4, 5, 6, 7, 0, 1, 2], 0, 4),
        ([4, 5, 6, 7, 0, 1, 2], 3, -1),
        ([1], 0, -1),
        ([1, 3], 3, 1),
        ([5, 1, 3], 5, 0),
        ([3, 1], 1, 1),
    ]
    passed = 0
    for k, (nums, target, expected) in enumerate(cases, 1):
        got = Solution().search(nums, target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}, target = {target}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
