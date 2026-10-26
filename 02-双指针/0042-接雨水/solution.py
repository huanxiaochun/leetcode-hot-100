"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        l, r = 0, len(height) - 1
        lmax = rmax = water = 0                    # 左边、右边见过的最高柱子
        while l < r:
            lmax = max(lmax, height[l])
            rmax = max(rmax, height[r])
            if lmax < rmax:                        # 左边是短板，l 处水位就是 lmax
                water += lmax - height[l]
                l += 1
            else:                                  # 右边是短板，r 处水位就是 rmax
                water += rmax - height[r]
                r -= 1
        return water


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1], 6),
        ([4, 2, 0, 3, 2, 5], 9),
        ([1], 0),
        ([3, 2, 1], 0),
        ([5, 0, 0, 5], 10),
    ]
    passed = 0
    for k, (height, expected) in enumerate(cases, 1):
        got = Solution().trap(height)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: height = {height}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
