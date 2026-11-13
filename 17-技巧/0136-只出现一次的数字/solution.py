"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        x = 0                                      # 0 异或任何数都不变
        for v in nums:
            x ^= v                                 # 成对的数异或后抵消成 0
        return x                                   # 剩下的就是只出现一次的那个


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 2, 1], 1),
        ([4, 1, 2, 1, 2], 4),
        ([1], 1),
        ([-1, 3, 3], -1),
        ([0, 7, 7, 0, 5], 5),
        ([-30000, 30000, -30000], 30000),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().singleNumber(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
