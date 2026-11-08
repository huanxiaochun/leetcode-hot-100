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
    def sortedArrayToBST(self, nums):
        def make(l, r):                            # 用 nums[l..r] 建一棵平衡 BST
            if l > r:
                return None
            mid = (l + r) // 2                     # 中间的数当根，左右个数最多差 1
            return TreeNode(nums[mid], make(l, mid - 1), make(mid + 1, r))
        return make(0, len(nums) - 1)


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


def inorder(t):
    return inorder(t.left) + [t.val] + inorder(t.right) if t else []


def height(t):
    """不平衡时返回 -1"""
    if not t:
        return 0
    l, r = height(t.left), height(t.right)
    return -1 if l < 0 or r < 0 or abs(l - r) > 1 else 1 + max(l, r)


if __name__ == "__main__":
    cases = [[-10, -3, 0, 5, 9], [1, 3], [0], [1, 2, 3, 4, 5, 6, 7], [-5, -1, 2, 8]]
    passed = 0
    for k, nums in enumerate(cases, 1):
        root = Solution().sortedArrayToBST(nums)
        ok = inorder(root) == nums and height(root) >= 0   # 答案不唯一：检查中序有序且高度平衡
        passed += ok
        print(f"用例 {k}: nums = {nums}")
        print(f"  输出: {to_level(root)}{'（中序就是 nums，且高度平衡）' if ok else '（不是平衡 BST）'}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
