"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()                                    # 排序后才能用双指针，也方便去重
        n, ans = len(nums), []
        for i in range(n - 2):
            if nums[i] > 0:                            # 最小的都大于 0，后面不可能凑出 0
                break
            if i > 0 and nums[i] == nums[i - 1]:       # 第一个数去重
                continue
            l, r = i + 1, n - 1
            while l < r:
                s = nums[i] + nums[l] + nums[r]
                if s < 0:                              # 太小，左边换大的
                    l += 1
                elif s > 0:                            # 太大，右边换小的
                    r -= 1
                else:
                    ans.append([nums[i], nums[l], nums[r]])
                    while l < r and nums[l] == nums[l + 1]:  # 跳过相同的第二个数
                        l += 1
                    while l < r and nums[r] == nums[r - 1]:  # 跳过相同的第三个数
                        r -= 1
                    l, r = l + 1, r - 1
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([-1, 0, 1, 2, -1, -4], [[-1, -1, 2], [-1, 0, 1]]),
        ([0, 1, 1], []),
        ([0, 0, 0], [[0, 0, 0]]),
        ([0, 0, 0, 0], [[0, 0, 0]]),
        ([-2, 0, 1, 1, 2], [[-2, 0, 2], [-2, 1, 1]]),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = sorted(Solution().threeSum(nums[:]))    # 会排序原数组，传副本；题目允许任意顺序
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
