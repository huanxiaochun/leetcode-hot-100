"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort()                           # 按左端点排序
        ans = []
        for l, r in intervals:
            if ans and l <= ans[-1][1]:
                ans[-1][1] = max(ans[-1][1], r)    # 和上一段重叠，延长右端点
            else:
                ans.append([l, r])                 # 不重叠，开新的一段
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([[1, 3], [2, 6], [8, 10], [15, 18]], [[1, 6], [8, 10], [15, 18]]),
        ([[1, 4], [4, 5]], [[1, 5]]),
        ([[4, 7], [1, 4]], [[1, 7]]),
        ([[1, 10], [2, 3], [4, 5]], [[1, 10]]),
        ([[5, 6]], [[5, 6]]),
    ]
    passed = 0
    for k, (intervals, expected) in enumerate(cases, 1):
        got = Solution().merge([iv[:] for iv in intervals])  # 会排序原数组，传副本
        ok = got == expected
        passed += ok
        print(f"用例 {k}: intervals = {intervals}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
