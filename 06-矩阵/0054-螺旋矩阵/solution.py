"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        ans = []
        top, bottom = 0, len(matrix) - 1                  # 四条边界，走完一条就往里收
        left, right = 0, len(matrix[0]) - 1
        while top <= bottom and left <= right:
            for j in range(left, right + 1):              # 上：左 -> 右
                ans.append(matrix[top][j])
            top += 1
            for i in range(top, bottom + 1):              # 右：上 -> 下
                ans.append(matrix[i][right])
            right -= 1
            if top <= bottom:                             # 还剩行，才走下边
                for j in range(right, left - 1, -1):
                    ans.append(matrix[bottom][j])
                bottom -= 1
            if left <= right:                             # 还剩列，才走左边
                for i in range(bottom, top - 1, -1):
                    ans.append(matrix[i][left])
                left += 1
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [1, 2, 3, 6, 9, 8, 7, 4, 5]),
        ([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]], [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]),
        ([[1]], [1]),
        ([[1, 2, 3]], [1, 2, 3]),
        ([[1], [2], [3]], [1, 2, 3]),
    ]
    passed = 0
    for k, (matrix, expected) in enumerate(cases, 1):
        got = Solution().spiralOrder(matrix)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: matrix = {matrix}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
