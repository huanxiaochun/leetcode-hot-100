"""
运行：
    python3 solution.py
"""
from collections import deque
from collections import Counter

class TreeNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def pathSum(self, root, targetSum):
        cnt = Counter({0: 1})                      # 空前缀：从根开始的路径也能被数到

        def dfs(node, s):                          # cnt 记录根到当前节点这条路上，各前缀和出现几次
            if not node:
                return 0
            s += node.val
            ans = cnt[s - targetSum]               # 以 node 结尾、和为 target 的路径条数
            cnt[s] += 1
            ans += dfs(node.left, s)               # 下端在左子树里的
            ans += dfs(node.right, s)              # 下端在右子树里的
            cnt[s] -= 1                            # 回溯：离开 node，它不再是后面节点的祖先
            return ans

        return dfs(root, 0)


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
        ([10, 5, -3, 3, 2, None, 11, 3, -2, None, 1], 8, 3),
        ([5, 4, 8, 11, None, 13, 4, 7, 2, None, None, 5, 1], 22, 3),
        ([], 0, 0),
        ([1], 1, 1),
        ([1000000000, 1000000000, None, 294967296, None, 1000000000, None, 1000000000, None, 1000000000], 0, 0),
    ]
    passed = 0
    for k, (vals, target, expected) in enumerate(cases, 1):
        got = Solution().pathSum(build(vals), target)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: root = {vals}, target = {target}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
