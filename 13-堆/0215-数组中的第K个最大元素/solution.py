"""
运行：
    python3 solution.py
"""
import heapq
from typing import List


class Solution:
    def findKthLargest(self, nums: List[int], k: int) -> int:
        h = []                                     # 小顶堆：只留目前最大的 k 个
        for x in nums:
            heapq.heappush(h, x)
            if len(h) > k:                         # 超过 k 个，扔掉里面最小的
                heapq.heappop(h)
        return h[0]                                # 最大的 k 个里最小的那个，就是第 k 大


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([3, 2, 1, 5, 6, 4], 2, 5),
        ([3, 2, 3, 1, 2, 4, 5, 5, 6], 4, 4),
        ([1], 1, 1),
        ([7, 7, 7], 2, 7),
        ([-1, 2, 0], 3, -1),
    ]
    passed = 0
    for idx, (nums, k, expected) in enumerate(cases, 1):
        got = Solution().findKthLargest(nums, k)
        ok = got == expected
        passed += ok
        print(f"用例 {idx}: nums = {nums}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
