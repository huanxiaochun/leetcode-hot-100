"""
运行：
    python3 solution.py
"""
class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        dp = [[False] * n for _ in range(n)]       # dp[i][j]：s[i..j] 是不是回文
        start, length = 0, 1
        for i in range(n - 1, -1, -1):             # i 从大到小：用到的 dp[i+1][..] 已经算好
            for j in range(i, n):
                # 两头相等，并且中间 s[i+1..j-1] 也是回文（长度 <= 2 时中间是空的或只有一个字）
                if s[i] == s[j] and (j - i < 2 or dp[i + 1][j - 1]):
                    dp[i][j] = True
                    if j - i + 1 > length:         # 更长，记下来
                        start, length = i, j - i + 1
        return s[start:start + length]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("babad", "bab"),
        ("cbbd", "bb"),
        ("a", "a"),
        ("ac", "a"),
        ("forgeeksskeegfor", "geeksskeeg"),
        ("aaaa", "aaaa"),
        ("abacdfgdcaba", "aba"),
    ]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().longestPalindrome(s)
        # 一样长的回文可能不止一个，都算对
        ok = len(got) == len(expected) and got == got[::-1] and got in s
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f'  输出: "{got}"   期望: "{expected}"   '
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
