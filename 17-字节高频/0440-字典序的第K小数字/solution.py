"""
运行：
    python3 solution.py
"""


class Solution:
    def findKthNumber(self, n: int, k: int) -> int:
        cur = 1
        k -= 1                                     # cur = 1 本身算一个
        while k > 0:
            steps = self.count(cur, n)
            if steps <= k:                         # 整棵子树跳过，去右兄弟
                k -= steps
                cur += 1
            else:                                  # 答案在子树里，往下一层
                cur *= 10
                k -= 1
        return cur

    def count(self, cur: int, n: int) -> int:
        """以 cur 为根、值不超过 n 的子树有多少个数"""
        steps, first, last = 0, cur, cur
        while first <= n:
            steps += min(last, n) - first + 1      # 这一层落在 [first, min(last, n)]
            first = first * 10
            last = last * 10 + 9
        return steps


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        (13, 2, 10), (1, 1, 1), (13, 6, 2), (100, 10, 17), (10, 3, 2),
        (1000000000, 1000000000, 999999999),
    ]
    sol = Solution()
    passed = 0
    for t, (n, k, expected) in enumerate(cases, 1):
        got = sol.findKthNumber(n, k)
        ok = got == expected
        passed += ok
        print(f"用例 {t}: n = {n}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")

    # 暴力对拍：n ≤ 300 的所有 k，和「转字符串排序」的结果比
    ok = True
    for n in range(1, 301):
        v = sorted(str(x) for x in range(1, n + 1))
        if any(sol.findKthNumber(n, k) != int(v[k - 1]) for k in range(1, n + 1)):
            ok = False
            break
    passed += ok
    print(f"用例 {len(cases) + 1}: 暴力对拍 n = 1~300 的全部 k   "
          + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")

    total = len(cases) + 1
    print(f"{passed}/{total} 通过")
    raise SystemExit(0 if passed == total else 1)
