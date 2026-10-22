"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def maxArea(self, height: List[int]) -> int:
        l, r, best = 0, len(height) - 1, 0
        while l < r:
            h = min(height[l], height[r])          # 水位由短板决定
            best = max(best, h * (r - l))
            if height[l] < height[r]:              # 移动短板，才可能变大
                l += 1
            else:
                r -= 1
        return best


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([1, 8, 6, 2, 5, 4, 8, 3, 7], 49),
        ([1, 1], 1),
        ([4, 3, 2, 1, 4], 16),
        ([1, 2, 1], 2),
        ([2, 3, 4, 5, 18, 17, 6], 17),
    ]
    passed = 0
    for k, (height, expected) in enumerate(cases, 1):
        got = Solution().maxArea(height)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: height = {height}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
