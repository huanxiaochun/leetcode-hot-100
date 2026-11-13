"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def sortColors(self, nums: List[int]) -> None:
        # [0, lo) 全是 0，[lo, i) 全是 1，(hi, n) 全是 2，[i, hi] 还没看
        lo, i, hi = 0, 0, len(nums) - 1
        while i <= hi:
            if nums[i] == 0:
                nums[i], nums[lo] = nums[lo], nums[i]   # 换来的是 1（或它自己），i 可以前进
                lo += 1
                i += 1
            elif nums[i] == 2:
                nums[i], nums[hi] = nums[hi], nums[i]
                hi -= 1                            # 换过来的数还没看过，i 不动
            else:
                i += 1                             # 1 就留在中间


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 0, 2, 1, 1, 0], [0, 0, 1, 1, 2, 2]),
        ([2, 0, 1], [0, 1, 2]),
        ([0], [0]),
        ([2, 2, 2], [2, 2, 2]),
        ([1, 0], [0, 1]),
        ([2, 1, 0, 2, 0, 1, 2], [0, 0, 1, 1, 2, 2, 2]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = nums[:]                              # 原地修改，拷贝一份保留输入
        Solution().sortColors(got)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
