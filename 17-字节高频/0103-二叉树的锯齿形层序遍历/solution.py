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
    def zigzagLevelOrder(self, root):
        ans = []
        if not root:
            return ans
        q = deque([root])
        left_to_right = True
        while q:
            level = []
            for _ in range(len(q)):                # 这一层有几个
                cur = q.popleft()
                level.append(cur.val)
                if cur.left:                       # 入队顺序始终从左到右
                    q.append(cur.left)
                if cur.right:
                    q.append(cur.right)
            if not left_to_right:
                level.reverse()
            ans.append(level)
            left_to_right = not left_to_right
        return ans


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


def show_vecs(v):
    return "[" + ",".join("[" + ",".join(map(str, x)) + "]" for x in v) + "]"


if __name__ == "__main__":
    cases = [
        ([3, 9, 20, None, None, 15, 7], [[3], [20, 9], [15, 7]]),
        ([1], [[1]]),
        ([], []),
        ([1, 2, 3, 4, 5, 6, 7], [[1], [3, 2], [4, 5, 6, 7]]),
        ([1, 2, 3, 4, None, None, 5], [[1], [3, 2], [4, 5]]),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = Solution().zigzagLevelOrder(build(vals))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: root = {show(vals)}")
        print(f"  输出: {show_vecs(got)}   期望: {show_vecs(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
