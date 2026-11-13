"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def deleteDuplicates(self, head):
        dummy = ListNode(0, head)
        p = dummy
        while p.next and p.next.next:
            if p.next.val == p.next.next.val:
                x = p.next.val                     # 这个值整段删掉
                while p.next and p.next.val == x:
                    p.next = p.next.next
            else:
                p = p.next                         # 唯一的，保留
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
        ([1, 2, 3, 3, 4, 4, 5], [1, 2, 5]),
        ([1, 1, 1, 2, 3], [2, 3]),
        ([], []),
        ([1, 1], []),
        ([1, 2, 2], [1]),
        ([1, 2, 3], [1, 2, 3]),
    ]
    passed = 0
    for k, (vals, expected) in enumerate(cases, 1):
        got = to_list(Solution().deleteDuplicates(build(vals)))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {fmt(vals)}")
        print(f"  输出: {fmt(got)}   期望: {fmt(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
