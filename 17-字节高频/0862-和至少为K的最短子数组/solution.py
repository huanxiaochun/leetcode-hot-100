"""
运行：
    python3 solution.py
"""
import random
from collections import deque
from math import inf
from typing import List


class Solution:
    def shortestSubarray(self, nums: List[int], k: int) -> int:
        n, ans = len(nums), inf
        P = [0] * (n + 1)
        for i, x in enumerate(nums):
            P[i + 1] = P[i] + x
        dq = deque()                                      # 存下标，P 单调递增
        for j in range(n + 1):
            while dq and P[j] - P[dq[0]] >= k:            # 队头配上 j 够了
                ans = min(ans, j - dq.popleft())
            while dq and P[dq[-1]] >= P[j]:               # j 当起点更好
                dq.pop()
            dq.append(j)
        return -1 if ans == inf else ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def brute(a, k):
    n, ans = len(a), inf
    for i in range(n):
        s = 0
        for j in range(i, n):
            s += a[j]
            if s >= k:
                ans = min(ans, j - i + 1)
                break
    return -1 if ans == inf else ans


if __name__ == "__main__":
    cases = [
        ([1], 1, 1),
        ([1, 2], 4, -1),
        ([2, -1, 2], 3, 3),
        ([84, -37, 32, 40, 95], 167, 3),
        ([17, 85, 93, -45, -21], 150, 2),
        ([-28, 81, -20, 28, -29], 89, 3),
    ]
    passed = 0
    for t, (nums, k, expected) in enumerate(cases, 1):
        got = Solution().shortestSubarray(nums, k)
        ok = got == expected
        passed += ok
        print(f"用例 {t}: nums = [{','.join(map(str, nums))}], k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    g = random.Random(862)
    ok = True
    for _ in range(20000):
        n, k = g.randint(1, 12), g.randint(1, 30)
        a = [g.randint(-20, 20) for _ in range(n)]
        if Solution().shortestSubarray(a, k) != brute(a, k):
            ok = False
            break
    passed += ok
    print(f"用例 {len(cases) + 1}: 和暴力对拍 2 万组（含负数）   "
          + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    total = len(cases) + 1
    print(f"{passed}/{total} 通过")
    raise SystemExit(0 if passed == total else 1)
