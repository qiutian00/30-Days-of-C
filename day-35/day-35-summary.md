# Day 35: Trie | 字典树

## Idea | 思路
- A tree where each edge is a character; words share common prefixes.
- A node's `is_end` flag marks the end of a word.

## Operations | 操作
- `insert`, `search`, `starts_with` are all O(L), L = word length.
- Independent of the number of stored words.

## Implementation | 实现
- Fixed 26-child array for lowercase letters (fast, memory-heavy).
- Alternatives: hash map per node, or compressed trie (Patricia).

## Autocomplete | 自动补全
- Descend to the prefix node, then DFS to collect all ending words.

## Applications | 应用
- Autocomplete, spell-check, IP longest-prefix routing, word games.
