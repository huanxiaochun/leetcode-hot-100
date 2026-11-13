"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        cand, cnt = 0, 0                           # 擂台上的候选人、他的票数
        for x in nums:
            if cnt == 0:
                cand = x                           # 擂台空了，x 上台
            cnt += 1 if x == cand else -1          # 相同加一票，不同就互相抵消一票
        return cand                                # 多数元素比其余加起来还多，最后留下的一定是它


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([3, 2, 3], 3),
        ([2, 2, 1, 1, 1, 2, 2], 2),
        ([1], 1),
        ([6, 5, 5], 5),
        ([1, 2, 3, 4, 4, 4, 4], 4),
        ([-1, -1, 7], -1),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().majorityElement(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
