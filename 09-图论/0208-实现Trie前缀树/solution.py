"""
运行：
    python3 solution.py
"""
# 每个结点有 26 个孩子，对应 a ~ z；从根往下走一条路就拼出一个前缀
class Node:
    __slots__ = ("child", "is_end")

    def __init__(self):
        self.child = [None] * 26
        self.is_end = False                        # 有单词正好在这里结束


class Trie:
    def __init__(self):
        self.root = Node()

    def _walk(self, s):                            # 沿着 s 往下走，走不通返回 None
        p = self.root
        for c in s:
            p = p.child[ord(c) - 97]
            if p is None:
                return None
        return p

    def insert(self, word: str) -> None:
        p = self.root
        for c in word:
            i = ord(c) - 97
            if p.child[i] is None:                 # 没有这条路就新建
                p.child[i] = Node()
            p = p.child[i]
        p.is_end = True

    def search(self, word: str) -> bool:
        p = self._walk(word)
        return p is not None and p.is_end          # 走得通，还得有单词在这里结束

    def startsWith(self, prefix: str) -> bool:
        return self._walk(prefix) is not None      # 走得通就行


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([("insert", "apple"), ("search", "apple"), ("search", "app"), ("startsWith", "app"),
          ("insert", "app"), ("search", "app")], [True, False, True, True]),
        ([("insert", "a"), ("search", "a"), ("startsWith", "a"), ("search", "b")], [True, True, False]),
        ([("insert", "car"), ("insert", "cat"), ("startsWith", "ca"), ("search", "ca"), ("search", "cat"),
          ("startsWith", "cb"), ("search", "cart")], [True, False, True, False, False]),
        ([("startsWith", "x"), ("insert", "xyz"), ("startsWith", "xyz"), ("search", "xy")], [False, True, False]),
    ]
    passed = 0
    for k, (ops, expected) in enumerate(cases, 1):
        t, got = Trie(), []
        for name, s in ops:
            r = getattr(t, name)(s)
            if name != "insert":
                got.append(r)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: " + " ".join(f'{n}("{s}")' for n, s in ops))
        print(f"  search / startsWith 的结果: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
