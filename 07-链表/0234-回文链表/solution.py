"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def isPalindrome(self, head):
        slow = fast = head
        while fast and fast.next:                  # 快指针走两步，慢指针走一步
            slow, fast = slow.next, fast.next.next
        prev = None                                # 从 slow 开始反转后半段
        while slow:
            nxt = slow.next
            slow.next = prev
            prev, slow = slow, nxt
        p, q = head, prev
        while q:                                   # 前半段和反转后的后半段逐个比
            if p.val != q.val:
                return False
            p, q = p.next, q.next
        return True


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
        ([1, 2, 2, 1], True),
        ([1, 2], False),
        ([1], True),
        ([1, 2, 3, 2, 1], True),
        ([1, 2, 3, 1], False),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = Solution().isPalindrome(build(vals))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {vals}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
