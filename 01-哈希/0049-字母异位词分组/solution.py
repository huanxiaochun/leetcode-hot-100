"""
运行：
    python3 solution.py
"""
from collections import defaultdict
from typing import List


class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        groups = defaultdict(list)             # 字母计数 -> 同组单词
        for s in strs:
            cnt = [0] * 26                     # 26 个字母各出现几次
            for c in s:
                cnt[ord(c) - ord("a")] += 1
            groups[tuple(cnt)].append(s)       # list 不能当 key，转成 tuple
        return list(groups.values())


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def normalize(groups):
    """题目允许任意顺序，比较前先排序"""
    return sorted(sorted(g) for g in groups)


if __name__ == "__main__":
    cases = [
        (["eat", "tea", "tan", "ate", "nat", "bat"], [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]),
        ([""], [[""]]),
        (["a"], [["a"]]),
        (["abc", "bca", "xyz", "cab", "zyx"], [["abc", "bca", "cab"], ["xyz", "zyx"]]),
        (["ab", "ba", "abb"], [["ab", "ba"], ["abb"]]),
    ]
    passed = 0
    for k, (strs, expected) in enumerate(cases, 1):
        got = normalize(Solution().groupAnagrams(strs))
        exp = normalize(expected)
        ok = got == exp
        passed += ok
        print(f"用例 {k}: strs = {strs}")
        print(f"  输出: {got}")
        print(f"  期望: {exp}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
