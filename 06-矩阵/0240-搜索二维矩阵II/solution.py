"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        i, j = 0, len(matrix[0]) - 1                      # 从右上角出发
        while i < len(matrix) and j >= 0:
            x = matrix[i][j]
            if x == target:
                return True
            if x > target:                                # 这一列往下都更大，整列排除
                j -= 1
            else:                                         # 这一行往左都更小，整行排除
                i += 1
        return False


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    M = [[1, 4, 7, 11, 15], [2, 5, 8, 12, 19], [3, 6, 9, 16, 22], [10, 13, 14, 17, 24], [18, 21, 23, 26, 30]]
    cases = [
        (M, 5, True),
        (M, 20, False),
        (M, 30, True),
        (M, 0, False),
        ([[-5]], -5, True),
        ([[1, 3, 5]], 4, False),
    ]
    passed = 0
    for k, (matrix, target, expected) in enumerate(cases, 1):
        got = Solution().searchMatrix(matrix, target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: matrix = {matrix}, target = {target}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
