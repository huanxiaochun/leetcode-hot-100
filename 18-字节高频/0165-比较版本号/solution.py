"""
运行：
    python3 solution.py
"""


class Solution:
    def compareVersion(self, version1: str, version2: str) -> int:
        m, n, i, j = len(version1), len(version2), 0, 0
        while i < m or j < n:
            x = y = 0                                     # 读完的串这一段就是 0
            while i < m and version1[i] != '.':
                x = x * 10 + int(version1[i])
                i += 1
            while j < n and version2[j] != '.':
                y = y * 10 + int(version2[j])
                j += 1
            if x != y:
                return 1 if x > y else -1
            i, j = i + 1, j + 1                           # 跳过 '.'
        return 0


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("1.2", "1.10", -1),       # 2 < 10，按字符串比会错
        ("1.01", "1.001", 0),
        ("1.0", "1.0.0.0", 0),
        ("0.1", "1.1", -1),
        ("1.0.1", "1", 1),
        ("7.5.2.4", "7.5.3", -1),
        ("1", "1.0.0.1", -1),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = Solution().compareVersion(a, b)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: version1 = "{a}", version2 = "{b}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
