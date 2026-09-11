# Day 31: Hash Table | 哈希表

## Idea | 思路
- Map key -> value in **O(1)** average time via a **hash function** and an array.

## Hash functions | 哈希函数
- Integer: `key % capacity` (use unsigned to avoid negative).
- String: **djb2** — `h = h * 33 + c`, start at 5381.

## Collision resolution | 冲突处理
- **Chaining (链地址)**: each bucket is a linked list; insert by prepend; search walks the list.
- **Open addressing (开放寻址)**: at most one entry per slot; probe `(idx + i) % CAP`.
  - Delete marks `DELETED` (tombstone), not `EMPTY`, to preserve the probe chain.

## Complexity | 复杂度
- Average O(1); worst case O(n) when many keys collide.

## Key terms | 术语
- **Load factor** = n / capacity; keep it low (e.g. < 0.75), resize when exceeded.
- Applications: symbol tables, caches, sets, dictionaries.
