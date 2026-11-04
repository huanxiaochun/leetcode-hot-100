"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def hasCycle(self, head):
        slow = fast = head
        while fast and fast.next:                  # 无环时 fast 会先走到 None
            slow = slow.next                       # 走一步
            fast = fast.next.next                  # 走两步
            if slow is fast:                       # 有环时 fast 一定会从后面追上 slow
                return True
        return False


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def build_cycle(vals, pos):
    """建一条链，再把尾巴接到下标 pos 的节点上（pos = -1 表示无环）"""
    nodes = [ListNode(v) for v in vals]
    for a, b in zip(nodes, nodes[1:]):
        a.next = b
    if pos >= 0:
        nodes[-1].next = nodes[pos]
    return nodes


if __name__ == "__main__":
    cases = [
        ([3, 2, 0, -4], 1, True),
        ([1, 2], 0, True),
        ([1], -1, False),
        ([1], 0, True),
        ([1, 2, 3], -1, False),
    ]
    passed = 0
    for k, (vals, pos, expected) in enumerate(cases, 1):
        nodes = build_cycle(vals, pos)
        got = Solution().hasCycle(nodes[0] if nodes else None)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {vals}, pos = {pos}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
