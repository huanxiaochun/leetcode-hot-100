"""
运行：
    python3 solution.py
"""


class Solution:
    def addStrings(self, num1: str, num2: str) -> str:
        i, j, carry = len(num1) - 1, len(num2) - 1, 0
        ans = []
        while i >= 0 or j >= 0 or carry:
            total = carry
            if i >= 0:
                total += ord(num1[i]) - ord('0')
                i -= 1
            if j >= 0:
                total += ord(num2[j]) - ord('0')
                j -= 1
            ans.append(str(total % 10))                   # 这一位
            carry = total // 10                           # 进位
        return ''.join(reversed(ans))


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("11", "123", "134"),
        ("456", "77", "533"),
        ("0", "0", "0"),
        ("999", "1", "1000"),
        ("1", "9999", "10000"),
        ("12345678901234567890", "98765432109876543210", "111111111011111111100"),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = Solution().addStrings(a, b)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: num1 = "{a}", num2 = "{b}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
