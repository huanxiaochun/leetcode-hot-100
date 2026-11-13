"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def canJump(self, nums: List[int]) -> bool:
        far = 0                                    # 目前能到达的最远下标
        for i, x in enumerate(nums):
            if i > far:                            # 走到了到不了的格子
                return False
            far = max(far, i + x)                  # 从 i 出发最远能到 i + x
            if far >= len(nums) - 1:               # 已经能到最后一格
                return True
        return True


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 3, 1, 1, 4], True),
        ([3, 2, 1, 0, 4], False),                  # 每条路都会停在下标 3 的 0 上
        ([0], True),                               # 起点就是终点
        ([0, 1], False),
        ([2, 0, 0], True),
        ([1, 1, 0, 1], False),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().canJump(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
