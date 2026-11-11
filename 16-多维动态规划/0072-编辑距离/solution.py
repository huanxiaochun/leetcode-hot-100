"""
运行：
    python3 solution.py
"""
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        # dp[i][j]：把 word1 前 i 个字符变成 word2 前 j 个字符，最少要几步
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(m + 1):
            dp[i][0] = i                           # 变成空串：全删掉
        for j in range(n + 1):
            dp[0][j] = j                           # 空串变过去：一个个插入
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    dp[i][j] = dp[i - 1][j - 1]    # 最后一个字符一样，不用动
                else:
                    dp[i][j] = 1 + min(dp[i - 1][j - 1],   # 替换
                                       dp[i - 1][j],       # 删除 word1 的最后一个
                                       dp[i][j - 1])       # 插入 word2 的最后一个
        return dp[m][n]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("horse", "ros", 3),
        ("intention", "execution", 5),
        ("", "abc", 3),
        ("abc", "", 3),
        ("abc", "abc", 0),
        ("kitten", "sitting", 3),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = Solution().minDistance(a, b)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: word1 = "{a}", word2 = "{b}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
