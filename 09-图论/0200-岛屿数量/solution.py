"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])

        def dfs(i, j):
            if i < 0 or j < 0 or i >= m or j >= n or grid[i][j] != "1":
                return
            grid[i][j] = "0"                       # 先淹掉再往外走，防止走回来
            dfs(i + 1, j)
            dfs(i - 1, j)
            dfs(i, j + 1)
            dfs(i, j - 1)

        cnt = 0
        for i in range(m):
            for j in range(n):
                if grid[i][j] == "1":              # 碰到一块没淹过的陆地：新岛
                    cnt += 1
                    dfs(i, j)                      # 把这座岛整个淹掉，以后不会再数到
        return cnt


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (["11110", "11010", "11000", "00000"], 1),
        (["11000", "11000", "00100", "00011"], 3),
        (["0"], 0),
        (["1"], 1),
        (["101", "010", "101"], 5),
        (["111", "101", "111"], 1),
    ]
    passed = 0
    for k, (rows, expected) in enumerate(cases, 1):
        got = Solution().numIslands([list(r) for r in rows])
        ok = got == expected
        passed += ok
        print(f"用例 {k}: grid = {rows}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
