"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeTwoLists(self, l1, l2):
        dummy = tail = ListNode()                  # 哨兵：不用单独处理头节点
        while l1 and l2:
            if l1.val <= l2.val:                   # 接上较小的那个
                tail.next, l1 = l1, l1.next
            else:
                tail.next, l2 = l2, l2.next
            tail = tail.next
        tail.next = l1 or l2                       # 剩下的直接接上
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
        ([1, 2, 4], [1, 3, 4], [1, 1, 2, 3, 4, 4]),
        ([], [], []),
        ([], [0], [0]),
        ([5], [1, 2, 3], [1, 2, 3, 5]),
        ([1, 1], [1], [1, 1, 1]),
    ]
    passed = 0
    for k, (a, b, expected) in enumerate(cases, 1):
        got = to_list(Solution().mergeTwoLists(build(a), build(b)))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: l1 = {a}, l2 = {b}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
