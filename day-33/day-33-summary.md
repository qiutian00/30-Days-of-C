# Day 33: Doubly & Circular Linked List | 双向与循环链表

## Doubly linked list | 双向链表
- Node has `prev` and `next`.
- Traverse both directions; `tail` gives O(1) back traversal.
- `erase(node)` is O(1) with only the node pointer — no search needed.

## Circular linked list | 循环链表
- Last node links back to the first; no `NULL`.
- Keep a pointer to `tail`; head is `tail->next`.
- Traverse with a `do...while` until back at the head.

## Applications | 应用
- Doubly: browser history, LRU cache, editors, playlists.
- Circular: round-robin scheduling, Josephus problem, ring buffers.
