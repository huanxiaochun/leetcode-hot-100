"""
运行：
    python3 solution.py
"""
class Node:                                        # LeetCode 已经定义好，本地运行需要自己写
    def __init__(self, x, next=None, random=None):
        self.val = x
        self.next = next
        self.random = random


class Solution:
    def copyRandomList(self, head):
        if not head:
            return None
        p = head                                   # ① 每个节点后面插一个复制：A A' B B' ...
        while p:
            p.next = Node(p.val, p.next)
            p = p.next.next
        p = head                                   # ② 复制的 random = 原 random 的复制
        while p:
            if p.random:
                p.next.random = p.random.next
            p = p.next.next
        copy_head, p = head.next, head             # ③ 拆成两条链，原链表恢复原样
        while p:
            c = p.next
            p.next = c.next
            c.next = c.next.next if c.next else None
            p = p.next
        return copy_head


# ============================================================
# ==                       本地测试                          ==
# ============================================================
def build_random(spec):
    """每个节点用 [val, random 的下标] 表示，None 表示 random 为空"""
    nodes = [Node(v) for v, _ in spec]
    for i, (_, r) in enumerate(spec):
        if i + 1 < len(nodes):
            nodes[i].next = nodes[i + 1]
        if r is not None:
            nodes[i].random = nodes[r]
    return nodes


def to_spec(head):
    nodes = []
    while head:
        nodes.append(head)
        head = head.next
    pos = {id(x): i for i, x in enumerate(nodes)}
    return [[x.val, pos[id(x.random)] if x.random else None] for x in nodes]


if __name__ == "__main__":
    cases = [
        [[7, None], [13, 0], [11, 4], [10, 2], [1, 0]],
        [[1, 1], [2, 1]],
        [[3, None], [3, 0], [3, None]],
        [],
        [[5, 0]],
    ]
    passed = 0
    for k, spec in enumerate(cases, 1):
        nodes = build_random(spec)
        head = nodes[0] if nodes else None
        copy = Solution().copyRandomList(head)
        orig = {id(x) for x in nodes}
        deep = True                                # 复制出来的节点不能和原节点是同一个
        p = copy
        while p:
            deep = deep and id(p) not in orig
            p = p.next
        got = to_spec(copy)
        ok = got == spec and deep and to_spec(head) == spec  # 原链表也要恢复
        passed += ok
        print(f"用例 {k}: head = {spec}")
        print(f"  输出: {got}{'（全新节点）' if deep else '（用了原节点！）'}   "
              + ("\033[32m通过\033[0m" if ok else "\033[31m失败\033[0m") + "\n")
    print(f"{passed}/{len(cases)} 通过")
    raise SystemExit(0 if passed == len(cases) else 1)
