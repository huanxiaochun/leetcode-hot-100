"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    # 归并排序：从中间切成两半，各自排好，再合并
    def sortList(self, head):
        if not head or not head.next:              # 0 或 1 个节点，本身有序
            return head
        slow, fast = head, head.next               # fast 先走一步：偶数个时 slow 停在左中点
        while fast and fast.next:
            slow, fast = slow.next, fast.next.next
        right, slow.next = slow.next, None         # 从中间切断
        return self.merge(self.sortList(head), self.sortList(right))

    def merge(self, a, b):                         # 合并两个有序链表（21 题）
        dummy = tail = ListNode()
        while a and b:
            if a.val <= b.val:                     # <= 保证稳定
                tail.next, a = a, a.next
            else:
                tail.next, b = b, b.next
            tail = tail.next
        tail.next = a or b
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
        ([4, 2, 1, 3], [1, 2, 3, 4]),
        ([-1, 5, 3, 4, 0], [-1, 0, 3, 4, 5]),
        ([], []),
        ([1], [1]),
        ([3, 3, 1, 2, 1], [1, 1, 2, 3, 3]),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = to_list(Solution().sortList(build(vals)))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {vals}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
