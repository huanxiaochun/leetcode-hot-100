"""
运行：
    python3 solution.py
"""
from bisect import bisect_left
from typing import List


class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        # tails[k] = 所有长度为 k + 1 的递增子序列里，最小的结尾
        # tails 一定是严格递增的，所以能二分
        tails = []
        for x in nums:
            k = bisect_left(tails, x)              # 第一个 >= x 的位置
            if k == len(tails):
                tails.append(x)                    # 比所有结尾都大：接在最长的后面
            else:
                tails[k] = x                       # 替换成更小的结尾，以后更容易接
        return len(tails)


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([10, 9, 2, 5, 3, 7, 101, 18], 4),
        ([0, 1, 0, 3, 2, 3], 4),
        ([7, 7, 7, 7], 1),
        ([5], 1),
        ([4, 10, 4, 3, 8, 9], 3),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().lengthOfLIS(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
