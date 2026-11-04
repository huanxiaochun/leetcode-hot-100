"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def removeNthFromEnd(self, head, n):
        dummy = ListNode(0, head)                  # 哨兵：删的是头节点也不用特判
        fast = slow = dummy
        for _ in range(n):                         # fast 先走 n 步
            fast = fast.next
        while fast.next:                           # 一起走，fast 到最后一个时 slow 在目标前一个
            fast, slow = fast.next, slow.next
        slow.next = slow.next.next
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


if __name__ == "__main__":
    cases = [
        ([1, 2, 3, 4, 5], 2, [1, 2, 3, 5]),
        ([1], 1, []),
        ([1, 2], 1, [1]),
        ([1, 2], 2, [2]),
        ([1, 2, 3], 3, [2, 3]),
    ]
    passed = 0
    for k, (vals, n, expected) in enumerate(cases, 1):
        got = to_list(Solution().removeNthFromEnd(build(vals), n))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {vals}, n = {n}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
