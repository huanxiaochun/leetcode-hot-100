"""
运行：
    python3 solution.py
"""
class Solution:
    def decodeString(self, s: str) -> str:
        st = []                                    # 进 [ 之前的现场：(外面已经拼好的串, 这一段要重复几次)
        cur, k = "", 0                             # 当前这一层正在拼的串、正在读的数字
        for c in s:
            if c.isdigit():
                k = k * 10 + int(c)                # 数字可能不止一位，比如 10[a]
            elif c == "[":
                st.append((cur, k))                # 保存现场，进入新的一层
                cur, k = "", 0
            elif c == "]":
                outer, times = st.pop()
                cur = outer + cur * times          # 这一层重复 times 次，接回到外面那一层后面
            else:
                cur += c
        return cur


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("3[a]2[bc]", "aaabcbc"),
        ("3[a2[c]]", "accaccacc"),
        ("2[abc]3[cd]ef", "abcabccdcdcdef"),
        ("abc3[cd]xyz", "abccdcdcdxyz"),
        ("10[a]", "aaaaaaaaaa"),
        ("2[a2[b2[c]]]", "abccbccabccbcc"),
    ]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().decodeString(s)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f'  输出: "{got}"   期望: "{expected}"   '
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
