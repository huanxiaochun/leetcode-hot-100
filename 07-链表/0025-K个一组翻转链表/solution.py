"""
运行：
    python3 solution.py
"""
class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseKGroup(self, head, k):
        dummy = ListNode(0, head)
        pre = dummy                                # 上一组的尾巴
        while True:
            tail = pre
            for _ in range(k):                     # 往后数 k 个，不够就结束
                tail = tail.next
                if not tail:
                    return dummy.next
            nxt = tail.next                        # 下一组的开头
            prev, cur = nxt, pre.next              # 组内反转，第一个节点直接指向下一组
            while cur is not nxt:
                t = cur.next
                cur.next = prev
                prev, cur = cur, t
            first = pre.next                       # 反转前的组头，现在是组尾
            pre.next = tail                        # 接上反转后的组头
            pre = first


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
        ([1, 2, 3, 4, 5], 2, [2, 1, 4, 3, 5]),
        ([1, 2, 3, 4, 5], 3, [3, 2, 1, 4, 5]),
        ([1, 2, 3, 4], 4, [4, 3, 2, 1]),
        ([1], 1, [1]),
        ([1, 2, 3, 4, 5, 6], 3, [3, 2, 1, 6, 5, 4]),
    ]
    passed = 0
    for idx, (vals, k, expected) in enumerate(cases, 1):
        got = to_list(Solution().reverseKGroup(build(vals), k))
        ok = got == expected
        passed += ok
        print(f"用例 {idx}: head = {vals}, k = {k}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
