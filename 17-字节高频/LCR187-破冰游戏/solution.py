"""
运行：
    python3 solution.py
"""


class Solution:
    def iceBreakingGame(self, num: int, target: int) -> int:
        f = 0                                             # 只剩 1 人时是 0 号
        for n in range(2, num + 1):
            f = (f + target) % n                          # 从 n-1 人推到 n 人
        return f


# ============================================================
# ==                       本地测试                          ==
# ============================================================
# 暴力模拟：真的一个个删，用来对拍
def simulate(num, target):
    people = list(range(num))
    idx = 0
    while len(people) > 1:
        idx = (idx + target - 1) % len(people)
        people.pop(idx)
    return people[0]


if __name__ == "__main__":
    cases = [
        (7, 4, 1),
        (12, 5, 0),
        (1, 1, 0),
        (5, 1, 4),                                        # 每次都是第一个离开，最后剩最后一个
        (100000, 1000000, -1),                            # -1 表示只看能否快速跑完，和下面的公式自比
    ]
    mark = lambda ok: "\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m"
    sol = Solution()
    passed = 0
    for k, (num, target, expected) in enumerate(cases, 1):
        got = sol.iceBreakingGame(num, target)
        ok = 0 <= got < num if expected == -1 else got == expected
        passed += ok
        print(f"用例 {k}: num = {num}, target = {target}")
        tail = f"   期望: {expected}" if expected != -1 else "   （规模最大的情况，O(num) 秒出）"
        print(f"  输出: {got}{tail}   " + mark(ok) + "\n")
    ok = all(sol.iceBreakingGame(num, t) == simulate(num, t) for num in range(1, 41) for t in range(1, 41))
    passed += ok
    print(f"用例 {len(cases) + 1}: 和暴力模拟对拍 num、target = 1~40   " + mark(ok) + "\n")

    total = len(cases) + 1
    print(f"{passed}/{total} 通过")
    raise SystemExit(0 if passed == total else 1)
