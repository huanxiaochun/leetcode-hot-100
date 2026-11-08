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
    # 返回值的含义：在 root 这棵子树里找 p、q
    #   p、q 都在里面 -> 返回它们的最近公共祖先
    #   只有一个在     -> 返回那一个
    #   都不在         -> 返回 None
    def lowestCommonAncestor(self, root, p, q):
        # 空树什么都没有；root 自己就是 p 或 q，直接把自己报上去，不用再往下找：
        # 如果另一个在它下面，它就是答案；如果另一个在别处，上面的节点会发现
        if not root or root is p or root is q:
            return root
        l = self.lowestCommonAncestor(root.left, p, q)     # 左子树找到了什么
        r = self.lowestCommonAncestor(root.right, p, q)    # 右子树找到了什么
        if l and r:                                # 一边一个：p、q 分在 root 两侧，root 就是答案
            return root
        return l or r                              # 只有一边有结果（可能是 p、q 之一，也可能是已经找到的答案）：原样往上传


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


def find(root, v):
    if not root or root.val == v:
        return root
    return find(root.left, v) or find(root.right, v)


if __name__ == "__main__":
    T = [3, 5, 1, 6, 2, 0, 8, None, None, 7, 4]
    cases = [(T, 5, 1, 3), (T, 5, 4, 5), ([1, 2], 1, 2, 1), (T, 7, 8, 3), (T, 6, 4, 5)]
    passed = 0
    for k, (vals, p, q, expected) in enumerate(cases, 1):
        root = build(vals)
        got = Solution().lowestCommonAncestor(root, find(root, p), find(root, q))
        ok = got is find(root, expected)           # 比较的是节点本身
        passed += ok
        print(f"用例 {k}: root = {vals}, p = {p}, q = {q}")
        print(f"  输出: {got.val if got else None}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
