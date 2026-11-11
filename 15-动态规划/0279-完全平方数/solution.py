"""
运行：
    python3 solution.py
"""
class Solution:
    def numSquares(self, n: int) -> int:
        # dp[i] = 和为 i 最少要几个完全平方数
        dp = [0] + [n] * n                         # 最多 n 个 1，用 n 当初始的「很大」
        for i in range(1, n + 1):
            j = 1
            while j * j <= i:                      # 最后一个数选 j²
                dp[i] = min(dp[i], dp[i - j * j] + 1)
                j += 1
        return dp[n]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [(12, 3), (13, 2), (1, 1), (4, 1), (7, 4), (43, 3), (10000, 1)]
    passed = 0
    for k, (n, expected) in enumerate(cases, 1):
        got = Solution().numSquares(n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: n = {n}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
