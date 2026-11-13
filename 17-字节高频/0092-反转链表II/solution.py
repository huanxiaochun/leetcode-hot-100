"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseBetween(self, head, left, right):
        dummy = ListNode(0, head)
        pre = dummy
        for _ in range(left - 1):                  # 停在第 left-1 个
            pre = pre.next
        cur = pre.next
        for _ in range(right - left):
            nxt = cur.next                         # 摘下 cur 后面那个
            cur.next = nxt.next
            nxt.next = pre.next                    # 插到 pre 后面
            pre.next = nxt
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
        ([1, 2, 3, 4, 5], 2, 4, [1, 4, 3, 2, 5]),
        ([5], 1, 1, [5]),
        ([1, 2, 3, 4, 5], 1, 5, [5, 4, 3, 2, 1]),
        ([1, 2, 3], 1, 2, [2, 1, 3]),
        ([1, 2, 3], 3, 3, [1, 2, 3]),
    ]
    passed = 0
    for k, (vals, left, right, expected) in enumerate(cases, 1):
        got = to_list(Solution().reverseBetween(build(vals), left, right))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: head = {fmt(vals)}, left = {left}, right = {right}")
        print(f"  输出: {fmt(got)}   期望: {fmt(expected)}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
