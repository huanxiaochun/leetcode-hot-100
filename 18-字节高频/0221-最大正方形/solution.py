"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        m, n, side = len(matrix), len(matrix[0]), 0
        dp = [[0] * (n + 1) for _ in range(m + 1)]        # 多一圈 0，不用判边界
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if matrix[i - 1][j - 1] == '1':
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1   # 上、左、左上取最短
                    side = max(side, dp[i][j])
        return side * side


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (["10100", "10111", "11111", "10010"], 4),
        (["01", "10"], 1),
        (["0"], 0),
        (["1"], 1),
        (["1111", "1111", "1111"], 9),
        (["11", "11", "10"], 4),
    ]
    passed = 0
    for k, (rows, expected) in enumerate(cases, 1):
        got = Solution().maximalSquare([list(r) for r in rows])
        ok = got == expected
        passed += ok
        print(f"用例 {k}: matrix = [{','.join(rows)}]")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
