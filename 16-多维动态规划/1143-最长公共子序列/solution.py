"""
运行：
    python3 solution.py
"""
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        m, n = len(text1), len(text2)
        # dp[i][j]：text1 前 i 个字符和 text2 前 j 个字符的 LCS 长度；第 0 行 / 列是空串，都是 0
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if text1[i - 1] == text2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1] + 1    # 最后一个字符相同：配成一对
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])   # 不同：扔掉其中一边的最后一个
        return dp[m][n]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("abcde", "ace", 3),
        ("abc", "abc", 3),
        ("abc", "def", 0),
        ("bsbininm", "jmjkbkjkv", 1),
        ("oxcpqrsvwf", "shmtulqrypy", 2),
        ("a", "a", 1),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = Solution().longestCommonSubsequence(a, b)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: text1 = "{a}", text2 = "{b}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
