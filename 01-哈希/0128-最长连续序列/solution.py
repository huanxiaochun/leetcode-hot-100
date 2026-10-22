"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        st = set(nums)                 # 去重 + O(1) 查找
        best = 0
        for x in st:                   # 遍历集合而不是 nums，重复值不会重复数
            if x - 1 in st:            # x-1 存在，x 不是起点
                continue
            y = x
            while y + 1 in st:         # 从起点往后数
                y += 1
            best = max(best, y - x + 1)
        return best                    # 每个数最多被数一次，总 O(n)


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([100, 4, 200, 1, 3, 2], 4),
        ([0, 3, 7, 2, 5, 8, 4, 6, 0, 1], 9),
        ([1, 0, 1, 2], 3),
        ([], 0),
        ([-3, -2, -1, 5], 3),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().longestConsecutive(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
