"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        n = len(nums)
        i = n - 2
        while i >= 0 and nums[i] >= nums[i + 1]:   # 1. 第一个「下降点」
            i -= 1
        if i >= 0:
            j = n - 1
            while nums[j] <= nums[i]:              # 2. 右边比它大的最小者
                j -= 1
            nums[i], nums[j] = nums[j], nums[i]
        nums[i + 1:] = nums[i + 1:][::-1]          # 3. 后缀变升序（i=-1 时整体反转）


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 3], [1, 3, 2]),
        ([3, 2, 1], [1, 2, 3]),
        ([1, 1, 5], [1, 5, 1]),
        ([1], [1]),
        ([1, 5, 8, 4, 7, 6, 5, 3, 1], [1, 5, 8, 5, 1, 3, 4, 6, 7]),
        ([1, 3, 2], [2, 1, 3]),
        ([2, 3, 1, 3, 3], [2, 3, 3, 1, 3]),        # 有重复元素
        ([5, 1, 1], [1, 1, 5]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = nums[:]                              # 原地修改，拷贝一份保留输入
        Solution().nextPermutation(got)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
