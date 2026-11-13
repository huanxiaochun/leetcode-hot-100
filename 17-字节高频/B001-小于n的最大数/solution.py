"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxLessThan(self, digits: List[int], n: int) -> int:
        m = n - 1                                         # < n 变成 ≤ m
        if m <= 0:
            return -1
        s = str(m)
        L = len(s)
        digits = sorted(set(digits))
        have = set(digits)
        mx = str(digits[-1])

        i = 0
        while i < L and int(s[i]) in have:                # 能照抄就照抄
            i += 1
        if i == L:                                        # 每一位都拼得出
            return m

        for j in range(i, -1, -1):                        # 从卡住的位置往前回退
            lower = -1
            for d in digits:                              # 比 s[j] 小的最大数字
                if d < int(s[j]):
                    lower = d
            if lower != -1:
                return int(s[:j] + str(lower) + mx * (L - j - 1))
        return int(mx * (L - 1)) if L > 1 else -1         # 少一位，全填最大数字


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 4, 9], 2533, 2499),     # 5 不在集合，放 4，后面填 9
        ([1, 2, 4, 9], 2411, 2299),     # m=2410：0、1 都没有更小的，退到 4 放 2
        ([1], 1111, 111),               # 同位数拼不出，少一位
        ([2, 3], 2, -1),                # m=1，一位都拼不出
        ([1, 2, 4, 9], 100, 99),        # m=99 本身就能拼
        ([5, 7], 50, 7),                # m=49：4 前没有更小的，少一位
        ([6, 7, 8], 5555, 888),
        ([2, 4, 9], 23122, 22999),      # 3 不在集合，第 2 位放 2
        ([9, 4, 2, 1], 2533, 2499),     # 数字没排序、没去重也要对
    ]
    passed = 0
    for k, (digits, n, expected) in enumerate(cases, 1):
        got = Solution().maxLessThan(digits, n)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: digits = [{','.join(map(str, digits))}], n = {n}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
