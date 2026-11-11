"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        m, n = len(board), len(board[0])

        def dfs(i, j, k):                          # 从 (i, j) 出发，能不能拼出 word[k:]
            if not (0 <= i < m and 0 <= j < n):    # 出界
                return False
            if board[i][j] != word[k]:             # 字母不对（走过的格子是 '#'，也不会相等）
                return False
            if k == len(word) - 1:                 # 最后一个字母也对上了
                return True
            c, board[i][j] = board[i][j], "#"      # 做选择：标记走过，不能再踩
            found = dfs(i + 1, j, k + 1) or dfs(i - 1, j, k + 1) or dfs(i, j + 1, k + 1) or dfs(i, j - 1, k + 1)
            board[i][j] = c                        # 撤销选择：恢复原字母
            return found

        return any(dfs(i, j, 0) for i in range(m) for j in range(n))   # 每个格子都可以当起点


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    b = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]]
    cases = [
        (b, "ABCCED", True),
        (b, "SEE", True),
        (b, "ABCB", False),
        ([["a"]], "a", True),
        ([["a", "a"]], "aaa", False),
    ]
    passed = 0
    for k, (board, word, expected) in enumerate(cases, 1):
        got = Solution().exist([row[:] for row in board], word)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: board = {["".join(r) for r in board]}, word = "{word}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
