"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reorderList(self, head):
        if not head or not head.next:
            return
        slow = fast = head
        while fast.next and fast.next.next:        # slow 停在左中点
            slow, fast = slow.next, fast.next.next
        second = self.reverse(slow.next)
        slow.next = None                           # 断开前半段
        first = head
        while second:                              # 交替接：前、后、前、后……
            n1, n2 = first.next, second.next
            first.next = second
            second.next = n1
            first, second = n1, n2

    def reverse(self, h):
        prev = None
        while h:
            nxt = h.next
            h.next = prev
            prev, h = h, nxt
        return prev


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


def fmt(v):
    return "[" + ",".join(map(str, v)) + "]"


if __name__ == "__main__":
    cases = [
        ([1, 2, 3, 4], [1, 4, 2, 3]),
        ([1, 2, 3, 4, 5], [1, 5, 2, 4, 3]),
        ([1], [1]),
        ([1, 2], [1, 2]),
        ([1, 2, 3], [1, 3, 2]),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        h = build(vals)
        Solution().reorderList(h)
        got = to_list(h)
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {fmt(vals)}")
        print(f"  输出: {fmt(got)}   期望: {fmt(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
