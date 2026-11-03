"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        n = len(nums)
        k %= n                                     # 转 n 次等于没转

        def rev(l, r):                             # 原地反转 nums[l..r]
            while l < r:
                nums[l], nums[r] = nums[r], nums[l]
                l, r = l + 1, r - 1

        rev(0, n - 1)                              # 整体反转
        rev(0, k - 1)                              # 前 k 个再反转回来
        rev(k, n - 1)                              # 后 n-k 个再反转回来


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 2, 3, 4, 5, 6, 7], 3, [5, 6, 7, 1, 2, 3, 4]),
        ([-1, -100, 3, 99], 2, [3, 99, -1, -100]),
        ([1, 2], 3, [2, 1]),
        ([1], 0, [1]),
        ([1, 2, 3], 3, [1, 2, 3]),
    ]
    passed = 0
    for idx, (nums, k, expected) in enumerate(cases, 1):
        got = nums[:]                              # 原地修改，拷贝一份保留输入
        Solution().rotate(got, k)
        ok = got == expected
        passed += ok
        print(f"用例 {idx}: nums = {nums}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
