"""
运行：
    python3 solution.py
"""
from collections import OrderedDict


class LRUCache:
    """OrderedDict = 哈希表 + 双向链表：越靠后越是最近用过"""

    def __init__(self, capacity: int):
        self.cap = capacity
        self.cache = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        self.cache.move_to_end(key)                # 用过了，挪到最后
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        if key in self.cache:                      # 已存在：挪到最后再改值
            self.cache.move_to_end(key)
        self.cache[key] = value
        if len(self.cache) > self.cap:             # 超了：删最前面那个，也就是最久没用的
            self.cache.popitem(last=False)


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (2, [("put", 1, 1), ("put", 2, 2), ("get", 1), ("put", 3, 3), ("get", 2),
             ("put", 4, 4), ("get", 1), ("get", 3), ("get", 4)], [1, -1, -1, 3, 4]),
        (1, [("put", 2, 1), ("get", 2), ("put", 3, 2), ("get", 2), ("get", 3)], [1, -1, 2]),
        (2, [("put", 1, 1), ("put", 2, 2), ("put", 1, 10), ("put", 3, 3), ("get", 1), ("get", 2)], [10, -1]),
        (2, [("get", 1), ("put", 1, 5), ("get", 1)], [-1, 5]),
    ]
    passed = 0
    for k, (cap, ops, expected) in enumerate(cases, 1):
        cache, got = LRUCache(cap), []
        for name, *args in ops:
            if name == "put":
                cache.put(*args)
            else:
                got.append(cache.get(*args))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: capacity = {cap}, " + " ".join(f"{n}({','.join(map(str, a))})" for n, *a in ops))
        print(f"  get 的结果: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
