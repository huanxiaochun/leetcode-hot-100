"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        words = set(wordDict)
        max_len = max(map(len, wordDict))          # 最长的词：最后一个词不会比它长
        n = len(s)
        # dp[i] = s 的前 i 个字符能不能拆成字典里的词
        dp = [True] + [False] * n                  # dp[0]：空串，什么都不拆
        for i in range(1, n + 1):
            for j in range(i - 1, max(-1, i - max_len - 1), -1):   # 最后一个词是 s[j:i]
                if dp[j] and s[j:i] in words:
                    dp[i] = True
                    break
        return dp[n]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("leetcode", ["leet", "code"], True),
        ("applepenapple", ["apple", "pen"], True),
        ("catsandog", ["cats", "dog", "sand", "and", "cat"], False),
        ("aaaaaaa", ["aaaa", "aaa"], True),
        ("cars", ["car", "ca", "rs"], True),
        ("ab", ["a"], False),
    ]
    passed = 0
    for k, (s, words, expected) in enumerate(cases, 1):
        got = Solution().wordBreak(s, words)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}", wordDict = {words}')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
