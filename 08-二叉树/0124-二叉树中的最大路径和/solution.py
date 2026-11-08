"""
运行：
    python3 solution.py
"""
from collections import deque
from math import inf

class TreeNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxPathSum(self, root):
        best = -inf                                # 节点值可能全是负数，不能从 0 开始

        def gain(node):                            # 从 node 往下走一条路，最多能贡献多少
            nonlocal best
            if not node:
                return 0
            l = max(0, gain(node.left))            # 贡献是负的，就不如不走那边
            r = max(0, gain(node.right))
            best = max(best, node.val + l + r)     # 以 node 为最高点、两边都走的路径
            return node.val + max(l, r)            # 交给父节点时只能选一边

        gain(root)
        return best


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
        ([1, 2, 3], 6),
        ([-10, 9, 20, None, None, 15, 7], 42),
        ([-3], -3),
        ([2, -1], 2),
        ([5, 4, 8, 11, None, 13, 4, 7, 2, None, None, None, 1], 48),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = Solution().maxPathSum(build(vals))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: root = {vals}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
