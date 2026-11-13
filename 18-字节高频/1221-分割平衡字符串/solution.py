"""
运行：
    python3 solution.py
"""


class Solution:
    def balancedStringSplit(self, s: str) -> int:
        balance = ans = 0
        for c in s:
            balance += 1 if c == 'R' else -1
            if balance == 0:                              # 刚好平衡，切一刀
                ans += 1
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("RLRRLLRLRL", 4),     # RL | RRLL | RL | RL
        ("RLRRRLLRLL", 2),     # RL | RRRLLRLL
        ("LLLLRRRR", 1),
        ("RLLLLRRRLR", 3),     # RL | LLLRRR | LR
        ("LR", 1),
    ]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().balancedStringSplit(s)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
