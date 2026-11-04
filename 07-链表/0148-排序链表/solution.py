"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


def split(head, n):
    """从 head 起保留 n 个节点并断开，返回后面部分的头"""
    for _ in range(n - 1):
        if not head:
            break
        head = head.next
    if not head:
        return None
    rest, head.next = head.next, None
    return rest


def merge(a, b, tail):
    """合并 a、b 接到 tail 后面，返回合并后的最后一个节点"""
    while a and b:
        if a.val <= b.val:
            tail.next, a = a, a.next
        else:
            tail.next, b = b, b.next
        tail = tail.next
    tail.next = a or b
    while tail.next:
        tail = tail.next
    return tail


class Solution:
    # 自底向上归并：每轮把长度为 step 的段两两合并，step = 1, 2, 4, ...
    def sortList(self, head):
        n, p = 0, head
        while p:
            n, p = n + 1, p.next
        dummy = ListNode(0, head)
        step = 1
        while step < n:
            tail, cur = dummy, dummy.next          # tail：已合并部分的最后一个节点
            while cur:
                left = cur
                right = split(left, step)          # 切出两段，各 step 个
                cur = split(right, step)
                tail = merge(left, right, tail)
            step *= 2
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
