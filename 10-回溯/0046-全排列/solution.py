"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        res, path = [], []                         # path：当前已经排好的前几位
        used = [False] * len(nums)                 # used[i]：nums[i] 是否已经在 path 里

        def dfs():
            if len(path) == len(nums):             # 每个数都用上了：得到一个排列
                res.append(path[:])                # 要拷贝，path 之后还会变
                return
            for i, x in enumerate(nums):
                if used[i]:                        # 用过的不能再选
                    continue
                used[i] = True                     # 做选择
                path.append(x)
                dfs()                              # 填下一位
                path.pop()                         # 撤销选择，换下一个数试
                used[i] = False

        dfs()
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 3], [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]),
        ([0, 1], [[0, 1], [1, 0]]),
        ([1], [[1]]),
        ([5, -1, 4], [[-1, 4, 5], [-1, 5, 4], [4, -1, 5], [4, 5, -1], [5, -1, 4], [5, 4, -1]]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = sorted(Solution().permute(nums))     # 题目允许任意顺序
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}")
        print(f"  期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
