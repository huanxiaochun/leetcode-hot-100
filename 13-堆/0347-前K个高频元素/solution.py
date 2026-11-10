"""
运行：
    python3 solution.py
"""
import heapq
from collections import Counter
from typing import List


class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        cnt = Counter(nums)                        # 先数每个数出现几次
        h = []                                     # 小顶堆，放 (次数, 数)：只留次数最多的 k 个
        for x, c in cnt.items():
            heapq.heappush(h, (c, x))
            if len(h) > k:                         # 超过 k 个，扔掉次数最少的
                heapq.heappop(h)
        return [x for _, x in h]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 1, 1, 2, 2, 3], 2, [1, 2]),
        ([1], 1, [1]),
        ([4, 1, -1, 2, -1, 2, 3], 2, [-1, 2]),
        ([5, 5, 6, 6, 6, 7], 1, [6]),
        ([1, 2], 2, [1, 2]),
    ]
    passed = 0
    for idx, (nums, k, expected) in enumerate(cases, 1):
        got = sorted(Solution().topKFrequent(nums, k))   # 题目允许任意顺序
        ok = got == expected
        passed += ok
        print(f"用例 {idx}: nums = {nums}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
