# Day 39: Skip List & Bloom Filter | 跳表与布隆过滤器

## Skip list | 跳表
- Sorted linked list + multiple "express" levels.
- Each node promoted with prob 1/2; search O(log n) average.
- Search top-left, skip ahead, drop down. Simpler than a balanced tree.

## Bloom filter | 布隆过滤器
- Probabilistic set: k hash functions set bits in a bit array.
- No false negatives; possible false positives.
- `contains` false -> definitely absent; true -> probably present.
- Space-efficient: O(m) bits; used to skip expensive lookups.

## Applications | 应用
- Skip list: Redis sorted sets, LSM-tree databases.
- Bloom filter: cache filtering, spell-check, routers, DB optimizers.
