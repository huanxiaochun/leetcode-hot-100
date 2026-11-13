"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def jump(self, nums: List[int]) -> int:
        steps = 0
        end = 0                                    # 跳 steps 次能到的最远下标：这一层的右边界
        far = 0                                    # 这一层里任意一格再跳一次，最远能到哪
        # 不用看最后一格：站到最后一格就已经到了，不必再起跳
        for i in range(len(nums) - 1):
            far = max(far, i + nums[i])
            if i == end:                           # 这一层走完了，必须再跳一次
                steps += 1
                end = far                          # 下一层的右边界
        return steps


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 3, 1, 1, 4], 2),                      # 0 -> 1 -> 4
        ([2, 3, 0, 1, 4], 2),
        ([0], 0),                                  # 已经在终点
        ([1, 2], 1),
        ([1, 1, 1, 1], 3),
        ([5, 1, 1, 1, 1], 1),
    ]
    passed = 0
    for k, (nums, expected) in enumerate(cases, 1):
        got = Solution().jump(nums)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
