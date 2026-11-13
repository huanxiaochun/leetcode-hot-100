"""
运行：
    python3 solution.py
"""
import random
from typing import List


class Solution:
    def sortArray(self, nums: List[int]) -> List[int]:
        def quick_sort(a, l, r):
            if l >= r:
                return
            pivot = a[random.randint(l, r)]               # 随机基准
            lt, i, gt = l, l, r
            while i <= gt:
                if a[i] < pivot:
                    a[i], a[lt] = a[lt], a[i]
                    lt += 1
                    i += 1
                elif a[i] > pivot:
                    a[i], a[gt] = a[gt], a[i]             # i 不动：换来的数还没看
                    gt -= 1
                else:
                    i += 1
            quick_sort(a, l, lt - 1)                      # < pivot
            quick_sort(a, gt + 1, r)                      # > pivot

        quick_sort(nums, 0, len(nums) - 1)
        return nums


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        [5, 2, 3, 1],
        [5, 1, 1, 2, 0, 0],
        [1],
        [],
        [2, 2, 2, 2, 2, 2],
        [-1, 3, -5, 0, 3, -1],
        [1, 2, 3, 4, 5],
        [5, 4, 3, 2, 1],
    ]
    # 再加一组大数据：5 万个数、只有 3 种值，二路划分会很慢，三路划分很快
    g = random.Random(42)
    cases.append([g.randrange(3) for _ in range(50000)])

    passed = 0
    for k, nums in enumerate(cases, 1):
        expected = sorted(nums)
        got = Solution().sortArray(nums[:])
        ok = got == expected
        passed += ok
        if len(nums) <= 20:
            print(f"用例 {k}: nums = {nums}")
            print(f"  输出: {got}   "
                  + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
        else:
            print(f"用例 {k}: n = {len(nums)}（只有 0/1/2 三种值）")
            print("  输出与 sorted 一致   "
                  + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
