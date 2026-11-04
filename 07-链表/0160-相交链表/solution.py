"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def getIntersectionNode(self, headA, headB):
        a, b = headA, headB
        while a is not b:                          # 两人都走 A + B 的总长度，会在交点（或 None）相遇
            a = a.next if a else headB             # 走完 A 换到 B
            b = b.next if b else headA             # 走完 B 换到 A
        return a


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def build(vals):
    dummy = tail = ListNode()
    for v in vals:
        tail.next = ListNode(v)
        tail = tail.next
    return dummy.next


def to_list(head):
    out = []
    while head:
        out.append(head.val)
        head = head.next
    return out


def concat(a, b):
    if not a:
        return b
    t = a
    while t.next:
        t = t.next
    t.next = b
    return a


if __name__ == "__main__":
    cases = [
        ([4, 1], [5, 6, 1], [8, 4, 5]),
        ([1, 9, 1], [3], [2, 4]),
        ([2, 6, 4], [1, 5], []),
        ([], [7], [3, 5]),
        ([1], [], [2]),
    ]
    passed = 0
    for k, (a, b, common) in enumerate(cases, 1):
        c = build(common)
        got = Solution().getIntersectionNode(concat(build(a), c), concat(build(b), c))
        ok = got is c                              # 必须是同一个节点，不只是值相等
        passed += ok
        print(f"用例 {k}: A = {a} + 公共 {common}, B = {b} + 公共")
        print(f"  输出: {got.val if got else None}   期望: {c.val if c else None}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
