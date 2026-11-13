"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def sortOddEvenList(self, head):
        if not head or not head.next:
            return head
        # 1. 拆成奇链、偶链
        odd, even_head = head, head.next
        even = even_head
        while even and even.next:
            odd.next = even.next
            odd = odd.next
            even.next = odd.next
            even = even.next
        odd.next = None
        # 2. 反转偶链，3. 合并
        return self.merge(head, self.reverse(even_head))

    def reverse(self, h):
        prev = None
        while h:
            nxt = h.next
            h.next = prev
            prev, h = h, nxt
        return prev

    def merge(self, a, b):
        dummy = p = ListNode()
        while a and b:
            if a.val <= b.val:
                p.next, a = a, a.next
            else:
                p.next, b = b, b.next
            p = p.next
        p.next = a or b
        return dummy.next


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
        ([1, 8, 3, 6, 5, 4, 7, 2], [1, 2, 3, 4, 5, 6, 7, 8]),
        ([1, 8, 3, 6, 5, 4, 7, 2, 9], [1, 2, 3, 4, 5, 6, 7, 8, 9]),
        ([5], [5]),
        ([2, 1], [1, 2]),
        ([1, 9, 2, 3, 5], [1, 2, 3, 5, 9]),   # 奇 1,2,5 升；偶 9,3 降
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = to_list(Solution().sortOddEvenList(build(vals)))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {fmt(vals)}")
        print(f"  输出: {fmt(got)}   期望: {fmt(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
