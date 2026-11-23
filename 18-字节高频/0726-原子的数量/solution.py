"""
运行：
    python3 solution.py
"""
from collections import Counter


class Solution:
    def countOfAtoms(self, formula: str) -> str:
        i, n = 0, len(formula)

        def num():                                        # 读数字，没有就是 1
            nonlocal i
            j = i
            while i < n and formula[i].isdigit():
                i += 1
            return int(formula[j:i] or 1)

        st = [Counter()]                                  # 栈：每层括号一张表
        while i < n:
            if formula[i] == '(':
                st.append(Counter())                      # 开新的一层
                i += 1
            elif formula[i] == ')':
                i += 1
                k = num()
                top = st.pop()
                for a, c in top.items():                  # 乘 k 后并回上一层
                    st[-1][a] += c * k
            else:
                j = i                                     # 大写字母开头
                i += 1
                while i < n and formula[i].islower():
                    i += 1
                st[-1][formula[j:i]] += num()
        return ''.join(a + (str(c) if c > 1 else '') for a, c in sorted(st[0].items()))


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("H2O", "H2O"),
        ("Mg(OH)2", "H2MgO2"),
        ("K4(ON(SO3)2)2", "K4N2O14S4"),
        ("Be32", "Be32"),
        ("((N42)24(OB40Li30CHe3O48LiNN26)33(C12Li48N30H13HBe31)21(BHN30Li26BCBe47N40)15(H5)16)14",
         "B18900Be18984C4200H5446He1386Li33894N50106O22638"),
        ("H50", "H50"),
        ("(H)", "H"),
    ]
    passed = 0
    for k, (formula, expected) in enumerate(cases, 1):
        got = Solution().countOfAtoms(formula)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: formula = "{formula}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
