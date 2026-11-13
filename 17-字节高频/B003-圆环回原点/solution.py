"""
运行：
    python3 solution.py
"""


class Solution:
    def backToOrigin(self, n: int, length: int = 10) -> int:
        dp = [0] * length
        dp[0] = 1                                         # 0 步：站在 0
        for _ in range(n):
            # 从左右邻居走过来；Python 的 % 对负数也返回非负，C++ 要先 + length
            dp = [dp[(j - 1) % length] + dp[(j + 1) % length] for j in range(length)]
        return dp[0]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (0, 10, 1),
        (1, 10, 0),
        (2, 10, 2),
        (3, 10, 0),       # 环长是偶数，奇数步回不去
        (4, 10, 6),       # C(4,2)，还绕不满一圈
        (10, 10, 254),    # C(10,5) = 252，再加顺时针、逆时针各绕一整圈 2 种
        (3, 3, 2),        # 环长 3：绕一整圈（顺/逆）
        (60, 10, 230585685502492596),   # n 的上限
    ]
    passed = 0
    for k, (n, length, expected) in enumerate(cases, 1):
        got = Solution().backToOrigin(n, length)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: n = {n}, 环长 = {length}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
