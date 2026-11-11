"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        res = []
        board = [["."] * n for _ in range(n)]
        # 每行只放一个，所以只要检查列和两条对角线
        # 同一条「/」对角线上 r + c 相同；同一条「\」对角线上 r - c 相同，加 n - 1 变成非负下标
        col, d1, d2 = [False] * n, [False] * (2 * n - 1), [False] * (2 * n - 1)

        def dfs(r):                                # 给第 r 行找位置
            if r == n:                             # n 行都放好了
                res.append(["".join(row) for row in board])
                return
            for c in range(n):
                if col[c] or d1[r + c] or d2[r - c + n - 1]:   # 剪枝：会被攻击
                    continue
                board[r][c] = "Q"                  # 做选择
                col[c] = d1[r + c] = d2[r - c + n - 1] = True
                dfs(r + 1)                         # 去放下一行
                board[r][c] = "."                  # 撤销选择
                col[c] = d1[r + c] = d2[r - c + n - 1] = False

        dfs(0)
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (4, [[".Q..", "...Q", "Q...", "..Q."], ["..Q.", "Q...", "...Q", ".Q.."]]),
        (1, [["Q"]]),
        (2, []),
        (3, []),
    ]
    passed = 0
    for k, (n, expected) in enumerate(cases, 1):
        got = Solution().solveNQueens(n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: n = {n}")
        print(f"  输出: {len(got)} 种摆法 {got}")
        print(f"  期望: {len(expected)} 种摆法   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
