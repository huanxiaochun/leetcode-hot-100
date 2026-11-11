"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        if not digits:                             # 空串要返回空列表，不是 [""]
            return []
        keys = ["", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"]
        res, path = [], []

        def dfs(i):                                # 第 i 位数字选哪个字母
            if i == len(digits):                   # 每一位都选好了
                res.append("".join(path))
                return
            for c in keys[int(digits[i])]:
                path.append(c)                     # 这一位选 c
                dfs(i + 1)                         # 去选下一位
                path.pop()                         # 撤销，换这个按键上的下一个字母

        dfs(0)
        return res


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("23", ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]),
        ("", []),
        ("2", ["a", "b", "c"]),
        ("79", ["pw", "px", "py", "pz", "qw", "qx", "qy", "qz", "rw", "rx", "ry", "rz", "sw", "sx", "sy", "sz"]),
    ]
    passed = 0
    for k, (digits, expected) in enumerate(cases, 1):
        got = Solution().letterCombinations(digits)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: digits = "{digits}"')
        print(f"  输出: {got}")
        print(f"  期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
