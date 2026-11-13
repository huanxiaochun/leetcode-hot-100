"""
运行：
    python3 solution.py
"""
from typing import List


class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        last = {c: i for i, c in enumerate(s)}     # 每个字母最后出现的位置
        ans = []
        start = end = 0                            # 当前片段的起点、至少要延伸到的位置
        for i, c in enumerate(s):
            end = max(end, last[c])                # 片段必须包住这个字母的最后一次出现
            if i == end:                           # 片段里所有字母都不会再出现：切一刀
                ans.append(end - start + 1)
                start = i + 1
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
if __name__ == "__main__":
    cases = [
        ("ababcbacadefegdehijhklij", [9, 7, 8]),
        ("eccbbbbdec", [10]),
        ("a", [1]),
        ("abc", [1, 1, 1]),
        ("abca", [4]),
        ("caedbdedda", [1, 9]),
    ]
    passed = 0
    for k, (s, expected) in enumerate(cases, 1):
        got = Solution().partitionLabels(s)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}"')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
