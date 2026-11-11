"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        candidates.sort()                          # 先排序，剪枝才能直接 break
        res, path = [], []

        # 还差 rest；只从 candidates[start:] 里挑，避免 [2,3] 和 [3,2] 这样的重复
        def dfs(start, rest):
            if rest == 0:                          # 正好凑够
                res.append(path[:])
                return
            for i in range(start, len(candidates)):
                x = candidates[i]
                if x > rest:                       # 剪枝：排过序，后面的只会更大
                    break
                path.append(x)
                dfs(i, rest - x)                   # 传 i 不是 i + 1：同一个数可以重复选
                path.pop()

        dfs(0, target)
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 3, 6, 7], 7, [[2, 2, 3], [7]]),
        ([2, 3, 5], 8, [[2, 2, 2, 2], [2, 3, 3], [3, 5]]),
        ([2], 1, []),
        ([7, 3, 2], 18, [[2, 2, 2, 2, 2, 2, 2, 2, 2], [2, 2, 2, 2, 2, 2, 3, 3], [2, 2, 2, 2, 3, 7], [2, 2, 2, 3, 3, 3, 3],
                         [2, 2, 7, 7], [2, 3, 3, 3, 7], [3, 3, 3, 3, 3, 3]]),
    ]
    passed = 0
    for k, (cand, target, expected) in enumerate(cases, 1):
        got = sorted(Solution().combinationSum(cand[:], target))   # 题目允许任意顺序
        ok = got == expected
        passed += ok
        print(f"用例 {k}: candidates = {cand}, target = {target}")
        print(f"  输出: {got}")
        print(f"  期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
