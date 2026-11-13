"""
运行：
    python3 solution.py
"""
from collections import deque


class TreeNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isCompleteTree(self, root):
        q = deque([root])
        seen_null = False
        while q:
            cur = q.popleft()
            if not cur:
                seen_null = True
                continue
            if seen_null:                          # 空位后面又出现了节点
                return False
            q.append(cur.left)                     # 空孩子也入队
            q.append(cur.right)
        return True


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def build(vals):
    """层序数组 -> 树，None 表示空节点"""
    if not vals or vals[0] is None:
        return None
    root = TreeNode(vals[0])
    q, i = deque([root]), 1
    while i < len(vals):
        cur = q.popleft()
        if vals[i] is not None:
            cur.left = TreeNode(vals[i])
            q.append(cur.left)
        if i + 1 < len(vals) and vals[i + 1] is not None:
            cur.right = TreeNode(vals[i + 1])
            q.append(cur.right)
        i += 2
    return root


def show(vals):
    return "[" + ",".join("null" if x is None else str(x) for x in vals) + "]"


if __name__ == "__main__":
    cases = [
        ([1, 2, 3, 4, 5, 6], True),
        ([1, 2, 3, 4, 5, None, 7], False),
        ([1, 2, 3, 4, None, 5], False),        # 单看每个节点都不缺左孩子，但中间夹了空位
        ([1], True),
        ([1, 2], True),
        ([1, None, 2], False),
        ([1, 2, 3, 4, 5, 6, 7], True),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = Solution().isCompleteTree(build(vals))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: root = {show(vals)}")
        print(f"  输出: {str(got).lower()}   期望: {str(expected).lower()}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
