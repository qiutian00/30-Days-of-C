# Day 22: Intro to Trees — Part 1 | 树的入门（一）

## Tree | 树
- Hierarchical, non-linear structure: nodes + edges; one **root**; each node has one parent and 0+ children.
- **Binary tree**: each node has at most a `left` and a `right` child.

## Terminology | 术语
- Root, leaf, internal node.
- Height of node = longest downward path to a leaf.
- Depth of node = path length from the root.
- Tree height = height of the root.

## Node | 节点
```c
struct TreeNode { int data; struct TreeNode *left, *right; };
```

## DFS Traversals | 深度优先遍历
- **Pre-order**:  Root → Left → Right
- **In-order**:   Left → Root → Right
- **Post-order**: Left → Right → Root

All O(n) time, O(h) stack.

## Demo tree output | 示例树输出
```
Pre-order : 1 2 4 5 3 6
In-order  : 4 2 5 1 3 6
Post-order: 4 5 2 6 3 1
```