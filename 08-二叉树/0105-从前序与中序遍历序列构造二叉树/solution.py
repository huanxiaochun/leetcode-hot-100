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
    def buildTree(self, preorder, inorder):
        pos = {v: i for i, v in enumerate(inorder)}   # 值 -> 在中序里的下标
        it = iter(preorder)                        # 前序里下一个要用的根

        def make(l, r):                            # 建出中序 [l, r] 这一段对应的子树
            if l > r:
                return None
            v = next(it)                           # 前序是 根 左 右：最前面的就是根
            m = pos[v]                             # 中序里根的左边是左子树，右边是右子树
            left = make(l, m - 1)                  # 前序里左子树紧跟在根后面，所以先建左边
            return TreeNode(v, left, make(m + 1, r))

        return make(0, len(inorder) - 1)


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
        ([3, 9, 20, 15, 7], [9, 3, 15, 20, 7], [3, 9, 20, None, None, 15, 7]),
        ([-1], [-1], [-1]),
        ([1, 2], [2, 1], [1, 2]),
        ([1, 2], [1, 2], [1, None, 2]),
        ([1, 2, 4, 5, 3, 6], [4, 2, 5, 1, 6, 3], [1, 2, 3, 4, 5, 6]),
    ]
    passed = 0
    for k, (pre, ino, expected) in enumerate(cases, 1):
        got = to_level(Solution().buildTree(pre, ino))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: preorder = {pre}, inorder = {ino}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
