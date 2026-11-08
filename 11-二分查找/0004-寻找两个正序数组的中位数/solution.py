"""
运行：
    python3 solution.py
"""
from math import inf
from typing import List


class Solution:
    # 把两个数组各切一刀，左边一共 half 个数，并且左边的最大值 <= 右边的最小值
    def findMedianSortedArrays(self, a: List[int], b: List[int]) -> float:
        if len(a) > len(b):                        # 在短的数组上二分
            return self.findMedianSortedArrays(b, a)
        m, n = len(a), len(b)
        half = (m + n + 1) // 2                    # 左半部分的个数（奇数时多放一个）
        l, r = 0, m                                # i = a 放进左半部分的个数，范围 [0, m]
        while l <= r:
            i = (l + r) // 2
            j = half - i                           # b 放进左半部分 j 个
            a_l = a[i - 1] if i > 0 else -inf      # 切口左右的四个数，越界用无穷代替
            a_r = a[i] if i < m else inf
            b_l = b[j - 1] if j > 0 else -inf
            b_r = b[j] if j < n else inf
            if a_l > b_r:                          # a 放多了
                r = i - 1
            elif b_l > a_r:                        # a 放少了
                l = i + 1
            else:                                  # 切对了
                left_max = max(a_l, b_l)
                if (m + n) % 2:
                    return float(left_max)
                return (left_max + min(a_r, b_r)) / 2


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 3], [2], 2.0),
        ([1, 2], [3, 4], 2.5),
        ([], [1], 1.0),
        ([2], [], 2.0),
        ([1, 3, 8, 9, 15], [7, 11, 18, 19, 21, 25], 11.0),
        ([-5, -3], [-4, 10], -3.5),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = Solution().findMedianSortedArrays(a, b)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums1 = {a}, nums2 = {b}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
