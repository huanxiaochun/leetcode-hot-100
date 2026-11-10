"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        ans = [0] * len(temperatures)              # 等不到更暖的一天就是 0
        st = []                                    # 还在等的日子（存下标），温度从栈底到栈顶不升
        for i, t in enumerate(temperatures):
            while st and temperatures[st[-1]] < t:
                j = st.pop()                       # 今天比第 j 天暖和：第 j 天等到了
                ans[j] = i - j
            st.append(i)                           # 今天也开始等
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([73, 74, 75, 71, 69, 72, 76, 73], [1, 1, 4, 2, 1, 1, 0, 0]),
        ([30, 40, 50, 60], [1, 1, 1, 0]),
        ([30, 60, 90], [1, 1, 0]),
        ([90, 80, 70], [0, 0, 0]),
        ([50, 50, 51], [2, 1, 0]),
    ]
    passed = 0
    for k, (t, expected) in enumerate(cases, 1):
        got = Solution().dailyTemperatures(t)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: temperatures = {t}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
