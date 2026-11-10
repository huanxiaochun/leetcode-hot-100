"""
运行：
    python3 solution.py
"""
import heapq


# 把所有数分成两半：lo 放较小的一半，hi 放较大的一半，并且 lo 比 hi 多 0 或 1 个
# 中位数只和两个堆顶有关
class MedianFinder:
    def __init__(self):
        self.lo = []                               # 大顶堆（存负数）：堆顶是较小一半里最大的
        self.hi = []                               # 小顶堆：堆顶是较大一半里最小的

    def addNum(self, num: int) -> None:
        heapq.heappush(self.lo, -num)              # ① 先放进较小的一半
        heapq.heappush(self.hi, -heapq.heappop(self.lo))   # ② 把较小一半里最大的挪过去，保证 lo 都 <= hi
        if len(self.hi) > len(self.lo):            # ③ hi 多了就还一个回来
            heapq.heappush(self.lo, -heapq.heappop(self.hi))

    def findMedian(self) -> float:
        if len(self.lo) > len(self.hi):            # 奇数个：中间那个在 lo 顶
            return float(-self.lo[0])
        return (-self.lo[0] + self.hi[0]) / 2      # 偶数个：两个堆顶的平均


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ([("add", 1), ("add", 2), ("find",), ("add", 3), ("find",)], [1.5, 2.0]),
        ([("add", 5), ("find",), ("add", 15), ("find",), ("add", 1), ("find",), ("add", 3), ("find",)], [5, 10, 5, 4]),
        ([("add", -1), ("find",), ("add", -2), ("find",), ("add", -3), ("find",), ("add", -4), ("find",)], [-1, -1.5, -2, -2.5]),
        ([("add", 6), ("add", 10), ("add", 2), ("add", 6), ("find",), ("add", 5), ("find",)], [6, 6]),
    ]
    passed = 0
    for k, (ops, expected) in enumerate(cases, 1):
        mf, got = MedianFinder(), []
        for name, *args in ops:
            if name == "add":
                mf.addNum(*args)
            else:
                got.append(mf.findMedian())
        ok = got == expected
        passed += ok
        print(f"用例 {k}: " + " ".join(f"addNum({a[0]})" if n == "add" else "findMedian()" for n, *a in ops))
        print(f"  findMedian 的结果: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
