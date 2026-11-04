"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapPairs(self, head):
        dummy = ListNode(0, head)
        prev = dummy                               # 这一对前面的节点
        while prev.next and prev.next.next:
            a, b = prev.next, prev.next.next
            a.next = b.next                        # ① a 指向下一对
            b.next = a                             # ② b 指向 a
            prev.next = b                          # ③ prev 指向 b
            prev = a                               # 交换后 a 在后面，成为下一对的 prev
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
        ([1, 2, 3, 4], [2, 1, 4, 3]),
        ([], []),
        ([1], [1]),
        ([1, 2, 3], [2, 1, 3]),
        ([1, 2, 3, 4, 5, 6], [2, 1, 4, 3, 6, 5]),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = to_list(Solution().swapPairs(build(vals)))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {vals}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
