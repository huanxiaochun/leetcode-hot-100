"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def findAnagrams(self, s: str, p: str) -> List[int]:
        m, ans = len(p), []
        if len(s) < m:
            return ans
        need, win = [0] * 26, [0] * 26             # p 的字母计数、窗口的字母计数
        for c in p:
            need[ord(c) - ord("a")] += 1
        for r, c in enumerate(s):
            win[ord(c) - ord("a")] += 1            # 右边进一个
            if r >= m:                             # 左边出一个，窗口长度保持 m
                win[ord(s[r - m]) - ord("a")] -= 1
            if r >= m - 1 and win == need:         # 26 位比较，O(1)
                ans.append(r - m + 1)
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("cbaebabacd", "abc", [0, 6]),
        ("abab", "ab", [0, 1, 2]),
        ("a", "ab", []),
        ("aaaa", "aa", [0, 1, 2]),
        ("baa", "aa", [1]),
    ]
    passed = 0
    for k, (s, p, expected) in enumerate(cases, 1):
        got = Solution().findAnagrams(s, p)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}", p = "{p}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
