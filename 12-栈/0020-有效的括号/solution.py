"""
运行：
    python3 solution.py
"""
class Solution:
    def isValid(self, s: str) -> bool:
        pairs = {")": "(", "]": "[", "}": "{"}      # 右括号 -> 对应的左括号
        st = []                                    # 还没配上的左括号
        for c in s:
            if c in pairs:                         # 右括号：必须和最近的那个左括号配对
                if not st or st[-1] != pairs[c]:
                    return False
                st.pop()
            else:
                st.append(c)                       # 左括号：先存起来，等右括号来配
        return not st                              # 还剩左括号没配上也不合法


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [("()", True), ("()[]{}", True), ("(]", False), ("([)]", False), ("{[]}", True), ("(((", False), ("]", False)]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().isValid(s)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
