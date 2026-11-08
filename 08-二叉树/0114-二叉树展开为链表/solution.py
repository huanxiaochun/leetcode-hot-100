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
    def flatten(self, root):
        cur = root
        while cur:
            if cur.left:
                pre = cur.left
                while pre.right:                   # 左子树最右边的节点：前序里它后面紧跟着 cur.right
                    pre = pre.right
                pre.right = cur.right              # 右子树接到它后面
                cur.right, cur.left = cur.left, None   # 左子树整个挪到右边
            cur = cur.right


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


def to_level(root):
    """树 -> 层序数组，去掉末尾的 None"""
    out, q = [], deque([root])
    while q:
        cur = q.popleft()
        if cur is None:
            out.append(None)
            continue
        out.append(cur.val)
        q.extend([cur.left, cur.right])
    while out and out[-1] is None:
        out.pop()
    return out


if __name__ == "__main__":
    cases = [
        ([1, 2, 5, 3, 4, None, 6], [1, None, 2, None, 3, None, 4, None, 5, None, 6]),
        ([], []),
        ([0], [0]),
        ([1, 2, 3], [1, None, 2, None, 3]),
        ([1, None, 2, 3], [1, None, 2, None, 3]),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        root = build(vals)
        Solution().flatten(root)
        got = to_level(root)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: root = {vals}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
