"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        j = 0                                      # [0, j) 都是非零，保持原顺序
        for i in range(len(nums)):
            if nums[i] != 0:
                nums[i], nums[j] = nums[j], nums[i]  # 非零换到前面，零被换到后面
                j += 1


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([0, 1, 0, 3, 12], [1, 3, 12, 0, 0]),
        ([0], [0]),
        ([1, 2, 3], [1, 2, 3]),
        ([0, 0, 1], [1, 0, 0]),
        ([4, 0, 5, 0, 0, 6], [4, 5, 6, 0, 0, 0]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = nums[:]                              # 原地修改，拷贝一份保留输入
        Solution().moveZeroes(got)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
