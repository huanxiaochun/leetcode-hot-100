"""
运行：
    python3 solution.py
"""
import random
from typing import List


class Solution:
    def search(self, nums: List[int], target: int) -> bool:
        lo, hi = 0, len(nums) - 1
        while lo <= hi:
            mid = (lo + hi) // 2
            if nums[mid] == target:
                return True
            if nums[lo] == nums[mid]:              # 分不清哪边有序，缩一格
                lo += 1
            elif nums[lo] < nums[mid]:             # 左半有序
                if nums[lo] <= target < nums[mid]:
                    hi = mid - 1
                else:
                    lo = mid + 1
            else:                                  # 右半有序
                if nums[mid] < target <= nums[hi]:
                    lo = mid + 1
                else:
                    hi = mid - 1
        return False


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 5, 6, 0, 0, 1, 2], 0, True),
        ([2, 5, 6, 0, 0, 1, 2], 3, False),
        ([1, 0, 1, 1, 1], 0, True),
        ([1, 1, 1, 0, 1], 0, True),
        ([1, 1, 1, 1, 1, 1, 1, 1, 1, 13, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1], 13, True),
        ([1], 0, False),
        ([3, 1], 1, True),
    ]
    sol = Solution()
    passed = 0
    for k, (nums, target, expected) in enumerate(cases, 1):
        got = sol.search(nums, target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}, target = {target}")
        print(f"  输出: {str(got).lower()}   期望: {str(expected).lower()}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")

    # 随机对拍：随机生成带重复的旋转数组，和 in 比
    rng = random.Random(7)
    ok = True
    for _ in range(20000):
        n = rng.randint(1, 12)
        a = sorted(rng.randint(0, 4) for _ in range(n))
        r = rng.randrange(n)
        a = a[r:] + a[:r]
        t = rng.randint(0, 5)
        if sol.search(a, t) != (t in a):
            ok = False
            break
    passed += ok
    print(f"用例 {len(cases) + 1}: 随机对拍 2 万组（值域 0~4，重复很多）   "
          + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")

    total = len(cases) + 1
    print(f"{passed}/{total} 通过")
    raise SystemExit(0 if passed == total else 1)
