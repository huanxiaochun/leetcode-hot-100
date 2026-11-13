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
    def pathSum(self, root, targetSum):
        ans, path = [], []

        def dfs(node, rest):
            if not node:
                return
            path.append(node.val)
            rest -= node.val
            if not node.left and not node.right and rest == 0:   # 叶子且刚好凑够
                ans.append(path[:])                # 存一份拷贝
            dfs(node.left, rest)
            dfs(node.right, rest)
            path.pop()                             # 回溯

        dfs(root, targetSum)
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
        ([5, 4, 8, 11, None, 13, 4, 7, 2, None, None, 5, 1], 22, [[5, 4, 11, 2], [5, 8, 4, 5]]),
        ([1, 2, 3], 5, []),
        ([1, 2], 0, []),
        ([], 0, []),
        ([-2, None, -3], -5, [[-2, -3]]),          # 负数，不能按 rest<0 剪枝
        ([1, 2], 1, []),                           # 根不是叶子，不算
    ]
    passed = 0
    for k, (vals, target, expected) in enumerate(cases, 1):
        got = Solution().pathSum(build(vals), target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: root = {show(vals)}, targetSum = {target}")
        print(f"  输出: {show_vecs(got)}   期望: {show_vecs(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
