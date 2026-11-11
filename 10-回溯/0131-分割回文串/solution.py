"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n = len(s)
        pal = [[True] * n for _ in range(n)]       # pal[i][j]：s[i..j] 是不是回文
        # 两头相等，并且里面也是回文；i 从后往前，保证 pal[i + 1][j - 1] 先算好
        for i in range(n - 1, -1, -1):
            for j in range(i + 1, n):
                pal[i][j] = s[i] == s[j] and pal[i + 1][j - 1]
        res, path = [], []

        def dfs(start):                            # s[start:] 还没切
            if start == n:                         # 切完了
                res.append(path[:])
                return
            for end in range(start, n):
                if not pal[start][end]:            # 剪枝：这一段不是回文，不能这么切
                    continue
                path.append(s[start:end + 1])
                dfs(end + 1)                       # 剩下的部分接着切
                path.pop()

        dfs(0)
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("aab", [["a", "a", "b"], ["aa", "b"]]),
        ("a", [["a"]]),
        ("abba", [["a", "b", "b", "a"], ["a", "bb", "a"], ["abba"]]),
        ("efe", [["e", "f", "e"], ["efe"]]),
    ]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = sorted(Solution().partition(s))      # 题目允许任意顺序
        ok = got == sorted(expected)
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f"  输出: {got}")
        print(f"  期望: {sorted(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
