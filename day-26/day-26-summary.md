# Day 26: Queues | 队列

## FIFO | 先进先出
- Operations (all O(1)): `enqueue` (rear), `dequeue` (front), `front`, `isEmpty`.

## Implementations | 实现
- **Circular array**: a `size` field or `(rear+1)%CAP == front`; `% CAP` wraps indices into a ring.
- **Linked list**: `front` and `rear` pointers; enqueue appends to tail; dequeue removes head; no fixed capacity.

## When to use circular array vs linked list | 何时用循环数组 vs 链表
- Circular array: cache-friendly, no per-node allocation, but fixed capacity.
- Linked list: unbounded, slight pointer overhead per element.

## Applications | 应用
- BFS (Day 23 level-order, Day 27 graph BFS), scheduling, producer-consumer buffers.