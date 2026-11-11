"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res, path = [], []

        # open / close：已经放了几个左括号、几个右括号
        def dfs(open_, close):
            if len(path) == 2 * n:                 # 放满 2n 个，一定合法
                res.append("".join(path))
                return
            if open_ < n:                          # 左括号还没用完，就可以放
                path.append("(")
                dfs(open_ + 1, close)
                path.pop()
            if close < open_:                      # 右括号不能比左括号多
                path.append(")")
                dfs(open_, close + 1)
                path.pop()

        dfs(0, 0)
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (3, ["((()))", "(()())", "(())()", "()(())", "()()()"]),
        (1, ["()"]),
        (2, ["(())", "()()"]),
    ]
    passed = 0
    for k, (n, expected) in enumerate(cases, 1):
        got = Solution().generateParenthesis(n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: n = {n}")
        print(f"  输出: {got}")
        print(f"  期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
