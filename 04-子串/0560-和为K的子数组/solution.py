"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def subarraySum(self, nums: List[int], k: int) -> int:
        cnt = {0: 1}                               # 前缀和 -> 出现次数，含空前缀
        s = ans = 0
        for x in nums:
            s += x
            ans += cnt.get(s - k, 0)               # 前面有几个前缀和等于 s - k
            cnt[s] = cnt.get(s, 0) + 1
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 1, 1], 2, 2),
        ([1, 2, 3], 3, 2),
        ([1, -1, 0], 0, 3),
        ([3, 4, 7, 2, -3, 1, 4, 2], 7, 4),
        ([1], 0, 0),
    ]
    passed = 0
    for idx, (nums, k, expected) in enumerate(cases, 1):
        got = Solution().subarraySum(nums, k)
        ok = got == expected
        passed += ok
        print(f"用例 {idx}: nums = {nums}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
