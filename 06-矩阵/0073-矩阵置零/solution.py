"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        m, n = len(matrix), len(matrix[0])
        row0 = any(matrix[0][j] == 0 for j in range(n))   # 第 0 行本身有没有 0
        col0 = any(matrix[i][0] == 0 for i in range(m))   # 第 0 列本身有没有 0
        for i in range(1, m):
            for j in range(1, n):
                if matrix[i][j] == 0:
                    matrix[i][0] = matrix[0][j] = 0       # 用第 0 行、第 0 列当标记
        for i in range(1, m):
            for j in range(1, n):
                if matrix[i][0] == 0 or matrix[0][j] == 0:
                    matrix[i][j] = 0
        if row0:                                          # 最后再处理第 0 行 / 列
            for j in range(n):
                matrix[0][j] = 0
        if col0:
            for i in range(m):
                matrix[i][0] = 0


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([[1, 1, 1], [1, 0, 1], [1, 1, 1]], [[1, 0, 1], [0, 0, 0], [1, 0, 1]]),
        ([[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]], [[0, 0, 0, 0], [0, 4, 5, 0], [0, 3, 1, 0]]),
        ([[1]], [[1]]),
        ([[1, 0]], [[0, 0]]),
        ([[1, 2], [3, 0], [5, 6]], [[1, 0], [0, 0], [5, 0]]),
    ]
    passed = 0
    for k, (matrix, expected) in enumerate(cases, 1):
        got = [row[:] for row in matrix]                  # 原地修改，深拷贝一份
        Solution().setZeroes(got)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: matrix = {matrix}")
        print(f"  输出: {got}")
        print(f"  期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
