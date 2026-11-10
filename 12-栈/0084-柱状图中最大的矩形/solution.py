"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        h = [0] + heights + [0]                    # 两头各放一根高度 0 的哨兵：左边的永远不会弹出，右边的会把栈清空
        st, best = [], 0                           # st 存下标，高度从栈底到栈顶递增
        for i, x in enumerate(h):
            while st and h[st[-1]] > x:
                height = h[st.pop()]               # 以这根柱子的高度为矩形的高
                left = st[-1]                      # 左边第一根比它矮的
                best = max(best, height * (i - left - 1))   # 右边第一根比它矮的是 i，宽度是 (left, i) 之间
            st.append(i)
        return best


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [([2, 1, 5, 6, 2, 3], 10), ([2, 4], 4), ([1], 1), ([2, 2, 2], 6), ([5, 4, 1, 2], 8), ([0], 0)]
    passed = 0
    for k, (heights, expected) in enumerate(cases, 1):
        got = Solution().largestRectangleArea(heights)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: heights = {heights}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
