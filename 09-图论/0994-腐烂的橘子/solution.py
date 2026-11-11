"""
运行：
    python3 solution.py
"""
from collections import deque
from typing import List


class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        q = deque((i, j) for i in range(m) for j in range(n) if grid[i][j] == 2)   # 所有烂橘子一起当起点
        fresh = sum(row.count(1) for row in grid)
        minutes = 0
        while q and fresh:
            minutes += 1                           # 队列里现有的这一层，都在这一分钟往外传
            for _ in range(len(q)):
                i, j = q.popleft()
                for x, y in ((i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1)):
                    if 0 <= x < m and 0 <= y < n and grid[x][y] == 1:
                        grid[x][y] = 2             # 传染，下一分钟它也会往外传
                        fresh -= 1
                        q.append((x, y))
        return minutes if fresh == 0 else -1       # 还有新鲜的：它们和烂橘子不连通


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([[2, 1, 1], [1, 1, 0], [0, 1, 1]], 4),
        ([[2, 1, 1], [0, 1, 1], [1, 0, 1]], -1),
        ([[0, 2]], 0),
        ([[0]], 0),
        ([[1]], -1),
        ([[2, 1, 1, 1, 2]], 2),
    ]
    passed = 0
    for k, (grid, expected) in enumerate(cases, 1):
        got = Solution().orangesRotting([row[:] for row in grid])
        ok = got == expected
        passed += ok
        print(f"用例 {k}: grid = {grid}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
