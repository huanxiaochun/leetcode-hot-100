"""
运行：
    python3 solution.py
"""
from itertools import permutations
from typing import List


class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        nums = sorted(nums)                               # 相同的挨在一起
        n, ans, path, used = len(nums), [], [], [False] * len(nums)

        def dfs():
            if len(path) == n:
                ans.append(path[:])                       # 要拷贝
                return
            for i in range(n):
                if used[i]:
                    continue
                if i > 0 and nums[i] == nums[i - 1] and not used[i - 1]:   # 相同数按顺序用
                    continue
                used[i] = True
                path.append(nums[i])
                dfs()
                path.pop()
                used[i] = False

        dfs()
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        [1, 1, 2],
        [1, 2, 3],
        [2, 2, 1, 1],
        [1],
        [3, 3, 3],
        [1, 2, 2, 3, 3, 3],
    ]
    show = lambda v: "[" + ",".join(map(str, v)) + "]"
    passed = 0
    for k, nums in enumerate(cases, 1):
        got = Solution().permuteUnique(nums)
        # 期望：所有排列去重后按字典序排好
        expected = [list(p) for p in sorted(set(permutations(nums)))]
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {show(nums)}")
        out = f"  输出: [{','.join(show(p) for p in got)}]" if len(got) <= 6 else f"  输出 {len(got)} 个排列"
        print(out + f"   期望 {len(expected)} 个   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
