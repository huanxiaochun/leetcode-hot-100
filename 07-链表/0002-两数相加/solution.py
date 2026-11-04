"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def addTwoNumbers(self, l1, l2):
        dummy = tail = ListNode()
        carry = 0
        while l1 or l2 or carry:                   # 最后还有进位也要再出一位
            s = carry
            if l1:
                s, l1 = s + l1.val, l1.next
            if l2:
                s, l2 = s + l2.val, l2.next
            tail.next = ListNode(s % 10)           # 本位
            tail = tail.next
            carry = s // 10                        # 进位
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
        ([2, 4, 3], [5, 6, 4], [7, 0, 8]),
        ([0], [0], [0]),
        ([9, 9, 9, 9, 9, 9, 9], [9, 9, 9, 9], [8, 9, 9, 9, 0, 0, 0, 1]),
        ([5], [5], [0, 1]),
        ([1, 8], [0], [1, 8]),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = to_list(Solution().addTwoNumbers(build(a), build(b)))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: l1 = {a}, l2 = {b}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
