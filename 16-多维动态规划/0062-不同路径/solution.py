"""
运行：
    python3 solution.py
"""
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        # dp[j]：走到当前这一行第 j 格有几种走法（只留一行，一行一行往下滚）
        dp = [1] * n                               # 第一行：只能一直往右，每格都是 1 种
        for _ in range(1, m):
            for j in range(1, n):
                dp[j] += dp[j - 1]                 # 从上面来（旧 dp[j]）+ 从左边来（dp[j-1]）
        return dp[-1]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [(3, 7, 28), (3, 2, 3), (7, 3, 28), (3, 3, 6), (1, 1, 1), (1, 5, 1), (10, 10, 48620)]
    passed = 0
    for k, (m, n, expected) in enumerate(cases, 1):
        got = Solution().uniquePaths(m, n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: m = {m}, n = {n}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
