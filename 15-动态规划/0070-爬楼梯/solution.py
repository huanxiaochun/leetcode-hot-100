"""
运行：
    python3 solution.py
"""
class Solution:
    def climbStairs(self, n: int) -> int:
        # dp[i] = 爬到第 i 阶的方法数 = dp[i - 1] + dp[i - 2]
        a, b = 1, 1                                # dp[0]、dp[1]
        for _ in range(2, n + 1):
            a, b = b, a + b                        # 最后一步跨 1 阶或 2 阶；往前滚一格
        return b


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [(1, 1), (2, 2), (3, 3), (5, 8), (10, 89), (45, 1836311903)]
    passed = 0
    for k, (n, expected) in enumerate(cases, 1):
        got = Solution().climbStairs(n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: n = {n}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
