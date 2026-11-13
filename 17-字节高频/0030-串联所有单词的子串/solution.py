"""
运行：
    python3 solution.py
"""
import random
from collections import Counter
from typing import List


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        ans = []
        n, m, w = len(s), len(words), len(words[0])
        need = Counter(words)

        for offset in range(w):                           # w 种切法
            win = Counter()
            left, cnt = offset, 0
            for right in range(offset, n - w + 1, w):
                word = s[right:right + w]
                if word not in need:                      # 不在 words 里，窗口作废
                    win.clear()
                    cnt = 0
                    left = right + w
                    continue
                win[word] += 1
                cnt += 1
                while win[word] > need[word]:             # 这个词多了，从左边吐
                    win[s[left:left + w]] -= 1
                    left += w
                    cnt -= 1
                if cnt == m:                              # 刚好凑齐
                    ans.append(left)
                    win[s[left:left + w]] -= 1
                    left += w
                    cnt -= 1
        ans.sort()
        return ans


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def brute(s: str, words: List[str]) -> List[int]:
    """暴力：每个起点切出 m 个词，排序后和 words 比"""
    m, w = len(words), len(words[0])
    target = sorted(words)
    return [i for i in range(len(s) - m * w + 1)
            if sorted(s[i + k * w:i + (k + 1) * w] for k in range(m)) == target]


if __name__ == "__main__":
    cases = [
        ("barfoothefoobarman", ["foo", "bar"], [0, 9]),
        ("wordgoodgoodgoodbestword", ["word", "good", "best", "word"], []),
        ("barfoofoobarthefoobarman", ["bar", "foo", "the"], [6, 9, 12]),
        ("aaaaaa", ["aa", "aa"], [0, 1, 2]),
        ("wordgoodgoodgoodbestword", ["word", "good", "best", "good"], [8]),
        ("a", ["a"], [0]),
    ]
    passed = 0
    for k, (s, words, expected) in enumerate(cases, 1):
        got = Solution().findSubstring(s, words)
        ok = got == expected
        passed += ok
        print(f'用例 {k}: s = "{s}", words = [{",".join(words)}]')
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    # 随机对拍：字母只有 a/b，单词长 1~3，重复和重叠很多
    rnd = random.Random(30)
    ok = True
    for _ in range(5000):
        w, m, n = rnd.randint(1, 3), rnd.randint(1, 3), rnd.randint(1, 20)
        s = ''.join(rnd.choice('ab') for _ in range(n))
        words = [''.join(rnd.choice('ab') for _ in range(w)) for _ in range(m)]
        if Solution().findSubstring(s, words) != brute(s, words):
            ok = False
            break
    passed += ok
    print(f"用例 {len(cases) + 1}: 和暴力对拍 5000 组   "
          + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    total = len(cases) + 1
    print(f"{passed}/{total} 通过")
    raise SystemExit(0 if passed == total else 1)
