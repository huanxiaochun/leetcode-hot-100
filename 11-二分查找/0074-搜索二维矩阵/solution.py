"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        l, r = 0, m * n                            # 按行拼起来就是一个长度 m*n 的有序数组
        while l < r:
            mid = (l + r) // 2
            x = matrix[mid // n][mid % n]          # 一维下标拆成行、列
            if x == target:
                return True
            if x < target:
                l = mid + 1
            else:
                r = mid
        return False


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    M = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]]
    cases = [(M, 3, True), (M, 13, False), (M, 60, True), ([[1]], 1, True), ([[1], [3]], 2, False)]
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
