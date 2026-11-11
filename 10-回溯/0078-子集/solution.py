"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res, path = [], []

        # 下一个数只从 nums[start:] 里挑，保证子集里的下标递增，不会重复
        def dfs(start):
            res.append(path[:])                    # 每个节点都是一个子集，一进来就收集
            for i in range(start, len(nums)):
                path.append(nums[i])               # 选 nums[i]
                dfs(i + 1)                         # 再从它后面挑
                path.pop()                         # 撤销，换下一个

        dfs(0)
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 3], [[], [1], [1, 2], [1, 2, 3], [1, 3], [2], [2, 3], [3]]),
        ([0], [[], [0]]),
        ([4, 9], [[], [4], [4, 9], [9]]),
        ([-1, 5, 2], [[], [-1], [-1, 2], [-1, 5], [-1, 5, 2], [2], [5], [5, 2]]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = sorted(Solution().subsets(nums))     # 题目允许任意顺序
        ok = got == sorted(expected)
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}")
        print(f"  期望: {sorted(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
