"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def closestMeetingNode(self, edges: List[int], node1: int, node2: int) -> int:
        def walk(start):
            # 从 start 沿唯一出边一直走，返回到每个点的距离，走不到的是 -1
            d = [-1] * len(edges)
            x, step = start, 0
            while x != -1 and d[x] == -1:                 # 走回走过的点就停（环）
                d[x] = step
                step += 1
                x = edges[x]
            return d

        d1, d2 = walk(node1), walk(node2)
        ans, best = -1, float("inf")
        for i in range(len(edges)):
            if d1[i] < 0 or d2[i] < 0:                    # 有一边到不了
                continue
            d = max(d1[i], d2[i])
            if d < best:                                  # 严格小于：平局留编号小的
                best, ans = d, i
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([2, 2, 3, -1], 0, 1, 2),
        ([1, 2, -1], 0, 2, 2),
        ([5, -1, 3, 4, 5, 6, -1, -1, 4, 3], 0, 0, 0),      # 同一个点，距离 0
        ([1, 2, 0], 0, 2, 0),                             # 环：0、1、2 的 max 分别是 1、2、2
        ([-1, -1], 0, 1, -1),                             # 谁也到不了谁
        ([4, 4, 8, -1, 9, 8, 4, 4, 1, 1], 5, 6, 1),
    ]
    passed = 0
    for k, (edges, node1, node2, expected) in enumerate(cases, 1):
        got = Solution().closestMeetingNode(edges, node1, node2)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: edges = {edges}, node1 = {node1}, node2 = {node2}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
