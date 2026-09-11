# Day 34: Deque | 双端队列

## Idea | 思路
- Insert/remove at **both ends** in O(1); generalizes stack and queue.

## Circular array implementation | 循环数组实现
- `front` = index of first element; `size` = count; back = `(front + size - 1) % CAP`.
- `push_front`: `front = (front - 1 + CAP) % CAP`.
- `push_back`: write at `(front + size) % CAP`.

## Linked-list implementation | 链表实现
- Doubly linked list: head = front, tail = back; no fixed capacity.

## Sliding window maximum | 滑动窗口最大值
- Deque holds candidate indices in decreasing order of value.
- Pop back while new element is larger; pop front when index leaves the window. O(n) total.

## Applications | 应用
- Sliding window, work-stealing schedulers, palindrome checks.
