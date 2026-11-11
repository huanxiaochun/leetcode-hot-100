"""
运行：
    python3 solution.py
"""
from collections import deque
from typing import List


class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        nxt = [[] for _ in range(numCourses)]      # nxt[b]：修完 b 之后才能修的课
        indeg = [0] * numCourses                   # 还差几门先修课
        for a, b in prerequisites:                 # [a, b]：先修 b 才能修 a，边 b -> a
            nxt[b].append(a)
            indeg[a] += 1
        q = deque(i for i in range(numCourses) if indeg[i] == 0)   # 没有先修课的，现在就能修
        done = 0
        while q:
            u = q.popleft()
            done += 1                              # 修完 u
            for v in nxt[u]:
                indeg[v] -= 1
                if indeg[v] == 0:                  # v 的先修课全修完了
                    q.append(v)
        return done == numCourses                  # 环上的课入度永远到不了 0


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (2, [[1, 0]], True),
        (2, [[1, 0], [0, 1]], False),
        (4, [[1, 0], [2, 0], [3, 1], [3, 2]], True),
        (3, [[0, 1], [1, 2], [2, 0]], False),
        (1, [], True),
        (5, [[1, 0], [2, 1], [3, 2], [1, 3], [4, 0]], False),
    ]
    passed = 0
    for k, (n, pre, expected) in enumerate(cases, 1):
        got = Solution().canFinish(n, pre)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: numCourses = {n}, prerequisites = {pre}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
