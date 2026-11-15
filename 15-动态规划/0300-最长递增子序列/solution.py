"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n, ans = len(nums), 1
        # dp[i] = 以 nums[i] 结尾的最长递增子序列的长度
        dp = [1] * n                               # 每个数自己就是长度 1
        for i in range(1, n):
            for j in range(i):                     # 看 i 左边的每一个数
                if nums[j] < nums[i]:              # 比 nums[i] 小，nums[i] 能接在它后面
                    dp[i] = max(dp[i], dp[j] + 1)
            ans = max(ans, dp[i])                  # 最长的不一定以最后一个数结尾
        return ans


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
