"""
运行：
    python3 solution.py
"""


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        last = {}                                  # 每个字符上次出现的下标
        l = best = 0                               # 窗口 [l, r] 内没有重复字符
        for r, c in enumerate(s):
            if last.get(c, -1) >= l:               # c 在窗口里出现过，左边界跳到它后面
                l = last[c] + 1
            last[c] = r
            best = max(best, r - l + 1)
        return best


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("abcabcbb", 3),
        ("bbbbb", 1),
        ("pwwkew", 3),
        ("", 0),
        ("abba", 2),
        ("dvdf", 3),
    ]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().lengthOfLongestSubstring(s)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
