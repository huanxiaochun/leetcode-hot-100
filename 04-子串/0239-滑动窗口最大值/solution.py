"""
运行：
    python3 solution.py
"""
from collections import deque
from typing import List


class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        dq, ans = deque(), []                      # 存下标，对应的值从队头到队尾单调递减
        for i, x in enumerate(nums):
            while dq and nums[dq[-1]] <= x:        # 比新来的小，以后不可能再是最大值
                dq.pop()
            dq.append(i)
            if dq[0] <= i - k:                     # 队头滑出窗口
                dq.popleft()
            if i >= k - 1:
                ans.append(nums[dq[0]])            # 队头就是窗口最大值
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 3, -1, -3, 5, 3, 6, 7], 3, [3, 3, 5, 5, 6, 7]),
        ([1], 1, [1]),
        ([1, -1], 1, [1, -1]),
        ([9, 8, 7, 6], 2, [9, 8, 7]),
        ([4, 2, 12, 3], 4, [12]),
    ]
    passed = 0
    for idx, (nums, k, expected) in enumerate(cases, 1):
        got = Solution().maxSlidingWindow(nums, k)
        ok = got == expected
        passed += ok
        print(f"用例 {idx}: nums = {nums}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
