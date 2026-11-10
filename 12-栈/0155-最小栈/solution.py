"""
运行：
    python3 solution.py
"""
from math import inf


# 再开一个栈 mn，和 st 一起压、一起弹：mn 的栈顶就是 st 里当前的最小值
class MinStack:
    def __init__(self):
        self.st = []
        self.mn = [inf]                            # 哨兵：省掉 push 时判空

    def push(self, val: int) -> None:
        self.st.append(val)
        self.mn.append(min(val, self.mn[-1]))      # 到这一层为止的最小值

    def pop(self) -> None:
        self.st.pop()
        self.mn.pop()                              # 弹掉后，mn 栈顶自动回到之前的最小值

    def top(self) -> int:
        return self.st[-1]

    def getMin(self) -> int:
        return self.mn[-1]


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([("push", -2), ("push", 0), ("push", -3), ("getMin",), ("pop",), ("top",), ("getMin",)], [-3, 0, -2]),
        ([("push", 1), ("push", 1), ("push", 2), ("getMin",), ("pop",), ("getMin",), ("pop",), ("getMin",)], [1, 1, 1]),
        ([("push", 5), ("getMin",), ("push", 3), ("getMin",), ("push", 7), ("getMin",),
          ("pop",), ("pop",), ("getMin",), ("top",)], [5, 3, 3, 5, 5]),
        ([("push", 2**31 - 1), ("getMin",), ("push", -2**31), ("getMin",), ("pop",), ("getMin",)],
         [2**31 - 1, -2**31, 2**31 - 1]),
    ]
    passed = 0
    for k, (ops, expected) in enumerate(cases, 1):
        ms, got = MinStack(), []
        for name, *args in ops:
            r = getattr(ms, name)(*args)
            if name in ("top", "getMin"):
                got.append(r)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: " + " ".join(f"{n}({','.join(map(str, a))})" for n, *a in ops))
        print(f"  top / getMin 的结果: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
