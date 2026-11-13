"""
运行：
    python3 solution.py
"""


class Solution:
    def mySqrt(self, x: int) -> int:
        lo, hi, ans = 0, x, 0
        while lo <= hi:
            mid = (lo + hi) // 2
            if mid * mid <= x:                     # Python 整数不溢出；C++ 要用 long long
                ans = mid                          # 可行，再往右试
                lo = mid + 1
            else:
                hi = mid - 1
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (4, 2), (8, 2), (0, 0), (1, 1), (2, 1), (15, 3), (16, 4),
        (2147395599, 46339), (2147483647, 46340),
    ]
    passed = 0
    for k, (x, expected) in enumerate(cases, 1):
        got = Solution().mySqrt(x)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: x = {x}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
