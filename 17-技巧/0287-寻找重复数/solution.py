"""
运行：
    python3 solution.py
"""
from typing import List


# 把 i -> nums[i] 看成链表的 next：值都在 [1, n]，从 0 出发一定会走进环
# 重复的数有两个下标指向它，它就是环的入口
class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        slow = fast = 0
        while True:
            slow = nums[slow]                      # 慢指针走 1 步
            fast = nums[nums[fast]]                # 快指针走 2 步
            if slow == fast:                       # 第一阶段：在环里相遇
                break
        slow = 0                                   # 一个回到起点
        while slow != fast:                        # 第二阶段：同速走，在环的入口相遇
            slow = nums[slow]
            fast = nums[fast]
        return slow


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 3, 4, 2, 2], 2),
        ([3, 1, 3, 4, 2], 3),
        ([3, 3, 3, 3, 3], 3),
        ([1, 1], 1),
        ([2, 2, 2], 2),
        ([1, 4, 4, 2, 4], 4),
        ([2, 5, 9, 6, 9, 3, 8, 9, 7, 1], 9),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().findDuplicate(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
