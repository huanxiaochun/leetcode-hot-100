"""
运行：
    python3 solution.py
"""
import random

# 力扣会提供 rand7()，本地用 random 模拟
_rng = random.Random(2026)
rand7_calls = 0


def rand7() -> int:
    global rand7_calls
    rand7_calls += 1
    return _rng.randint(1, 7)


class Solution:
    def rand10(self) -> int:
        while True:
            x = (rand7() - 1) * 7 + rand7()               # 均匀的 1~49
            if x <= 40:
                return (x - 1) % 10 + 1                   # 1~40 均匀映射到 1~10
            # 41~49 丢掉重来


# ============================================================
# ==                       本地测试                          ==
# ============================================================
# 随机算法没法比对固定输出，用两件事验证：值都在 1~10 内；每个值出现的频率接近 1/10
if __name__ == "__main__":
    N = 1000000
    sol = Solution()
    cnt = [0] * 11
    in_range = True
    for _ in range(N):
        v = sol.rand10()
        if v < 1 or v > 10:
            in_range = False
            break
        cnt[v] += 1

    # 卡方检验：9 个自由度，显著性 0.001 的临界值约 27.88，均匀分布时统计量几乎不会超过它
    expected = N / 10
    chi2 = sum((cnt[v] - expected) ** 2 / expected for v in range(1, 11))
    avg_calls = rand7_calls / N

    mark = lambda ok: "\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m"
    passed, total = 0, 3
    ok = in_range
    passed += ok
    print("用例 1: 输出都在 1~10 内   " + mark(ok) + "\n")
    ok = in_range and chi2 < 27.88
    passed += ok
    print(f"用例 2: 各值频率（{N} 次）：" + " ".join(f"{v}={cnt[v] / N:g}" for v in range(1, 11)))
    print(f"  卡方 = {chi2:g}（< 27.88 视为均匀）   " + mark(ok) + "\n")
    ok = abs(avg_calls - 2.45) < 0.05
    passed += ok
    print(f"用例 3: 平均每次调用 rand7 {avg_calls:g} 次（理论 2 × 49/40 = 2.45）   " + mark(ok) + "\n")

    print(f"{passed}/{total} 通过")
    raise SystemExit(0 if passed == total else 1)
