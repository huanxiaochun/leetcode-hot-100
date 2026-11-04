"""
运行：
    python3 solution.py
"""
import heapq


class ListNode:                                    # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeKLists(self, lists):
        # 堆里放 (值, 链的编号, 节点)：值相同时比编号，不会去比较节点本身
        h = [(node.val, i, node) for i, node in enumerate(lists) if node]
        heapq.heapify(h)
        dummy = tail = ListNode()
        while h:
            _, i, x = heapq.heappop(h)             # 当前所有链头里最小的
            tail.next = x
            tail = x
            if x.next:                             # 补上它所在链的下一个
                heapq.heappush(h, (x.next.val, i, x.next))
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
        ([[1, 4, 5], [1, 3, 4], [2, 6]], [1, 1, 2, 3, 4, 4, 5, 6]),
        ([], []),
        ([[]], []),
        ([[2], [], [1]], [1, 2]),
        ([[1, 2, 3]], [1, 2, 3]),
    ]
    passed = 0
    for k, (lists, expected) in enumerate(cases, 1):
        got = to_list(Solution().mergeKLists([build(v) for v in lists]))
        ok = got == expected
        passed += ok
        print(f"用例 {k}: lists = {lists}")
        print(f"  输出: {got}   期望: {expected}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
