"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        dp = [0] * n                               # dp[j]：走到当前这一行第 j 格的最小路径和
        dp[0] = grid[0][0]
        for j in range(1, n):                      # 第一行只能从左边来
            dp[j] = dp[j - 1] + grid[0][j]
        for i in range(1, m):
            dp[0] += grid[i][0]                    # 第一列只能从上面来
            for j in range(1, n):
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j]   # 上面（旧 dp[j]）、左边取小的
        return dp[-1]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([[1, 3, 1], [1, 5, 1], [4, 2, 1]], 7),
        ([[1, 2, 3], [4, 5, 6]], 12),
        ([[5]], 5),
        ([[1, 2, 3, 4]], 10),
        ([[1], [2], [3]], 6),
        ([[1, 9, 1, 1], [1, 9, 1, 9], [1, 1, 1, 1]], 6),
    ]
    passed = 0
    for k, (grid, expected) in enumerate(cases, 1):
        got = Solution().minPathSum(grid)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: grid = {grid}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
