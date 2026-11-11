"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        rows = []
        for i in range(numRows):
            row = [1] * (i + 1)                    # 两头都是 1
            for j in range(1, i):
                row[j] = rows[i - 1][j - 1] + rows[i - 1][j]   # 左上 + 正上
            rows.append(row)
        return rows


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (1, [[1]]),
        (2, [[1], [1, 1]]),
        (5, [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1]]),
        (6, [[1], [1, 1], [1, 2, 1], [1, 3, 3, 1], [1, 4, 6, 4, 1], [1, 5, 10, 10, 5, 1]]),
    ]
    passed = 0
    for k, (n, expected) in enumerate(cases, 1):
        got = Solution().generate(n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: numRows = {n}")
        print(f"  输出: {got}\n  期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
