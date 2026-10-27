"""
运行：
    python3 solution.py
"""
from collections import Counter
from math import inf


class Solution:
    def minWindow(self, s: str, t: str) -> str:
        need = Counter(t)                          # 还欠每个字符几个，负数表示多出来
        missing = len(t)                           # 还差几个字符没覆盖
        start, best, l = 0, inf, 0
        for r, c in enumerate(s):
            if need[c] > 0:                        # 进来的是需要的字符
                missing -= 1
            need[c] -= 1
            while missing == 0:                    # 已经全覆盖，收缩左边
                if r - l + 1 < best:
                    best, start = r - l + 1, l
                need[s[l]] += 1
                if need[s[l]] > 0:                 # 移出后又缺了，停止收缩
                    missing += 1
                l += 1
        return "" if best == inf else s[start:start + best]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("ADOBECODEBANC", "ABC", "BANC"),
        ("a", "a", "a"),
        ("a", "aa", ""),
        ("aa", "aa", "aa"),
        ("ab", "b", "b"),
        ("cabwefgewcwaefgcf", "cae", "cwae"),
    ]
    passed = 0
    for k, (s, t, expected) in enumerate(cases, 1):
        got = Solution().minWindow(s, t)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}", t = "{t}"')
        print(f'  输出: "{got}"   期望: "{expected}"   '
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
