"""
运行：
    python3 solution.py
"""


class MyQueue:
    def __init__(self):
        self.ins, self.out = [], []                       # 列表当栈：只用 append / pop / [-1]

    def push(self, x: int) -> None:
        self.ins.append(x)

    def pop(self) -> int:
        x = self.peek()                                   # peek 会保证 out 栈顶是队头
        self.out.pop()
        return x

    def peek(self) -> int:
        if not self.out:                                  # out 空了才倒
            while self.ins:
                self.out.append(self.ins.pop())
        return self.out[-1]

    def empty(self) -> bool:
        return not self.ins and not self.out


# ============================================================
# ==                       本地测试                          ==
# ============================================================
# 操作序列：push 带参数；pop/peek 期望返回值；empty 期望 0/1
if __name__ == "__main__":
    cases = [
        ([("push", 1), ("push", 2), ("peek",), ("pop",), ("empty",)], [1, 1, 0]),
        ([("push", 1), ("push", 2), ("pop",), ("push", 3), ("pop",), ("pop",), ("empty",)], [1, 2, 3, 1]),
        ([("empty",), ("push", 5), ("empty",), ("peek",), ("pop",), ("empty",)], [1, 0, 5, 5, 1]),
        # out 里还有元素时再 push，不能倒：先出 2，再出 3、4
        ([("push", 1), ("push", 2), ("pop",), ("push", 3), ("push", 4), ("peek",), ("pop",), ("pop",), ("pop",)],
         [1, 2, 2, 3, 4]),
    ]
    passed = 0
    for k, (ops, expected) in enumerate(cases, 1):
        q, got = MyQueue(), []
        for name, *args in ops:
            r = getattr(q, name)(*args)
            if name != "push":
                got.append(int(r))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: " + ", ".join(f"{n}({a[0]})" if a else n for n, *a in ops))
        print(f"  返回: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
