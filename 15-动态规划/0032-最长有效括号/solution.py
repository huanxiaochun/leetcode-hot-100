"""
运行：
    python3 solution.py
"""
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        n, best = len(s), 0
        # dp[i] = 以 s[i] 结尾的最长有效括号子串的长度；以 ( 结尾的一定是 0
        dp = [0] * n
        for i in range(1, n):
            if s[i] == "(":
                continue
            j = i - 1 - dp[i - 1]                  # 跳过 i - 1 结尾的那一段，看它前面那个字符
            if j >= 0 and s[j] == "(":
                dp[i] = dp[i - 1] + 2              # s[j] 和 s[i] 配成一对，把中间那段包起来
                if j >= 1:
                    dp[i] += dp[j - 1]             # 再接上 j 前面紧挨着的那一段
            best = max(best, dp[i])
        return best


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [("(()", 2), (")()())", 4), ("", 0), ("()(())", 6), ("(()())", 6), ("())((())", 4), ("((((", 0)]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().longestValidParentheses(s)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
