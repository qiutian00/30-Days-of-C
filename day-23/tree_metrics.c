#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left, *right;
};

struct TreeNode *newNode(int data)
{
    struct TreeNode *n = malloc(sizeof(*n));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

int height(struct TreeNode *r)
{
    if (!r) return 0;
    int hl = height(r->left);
    int hr = height(r->right);
    return 1 + (hl > hr ? hl : hr);
}

int countNodes(struct TreeNode *r)
{
    if (!r) return 0;
    return 1 + countNodes(r->left) + countNodes(r->right);
}

int countLeaves(struct TreeNode *r)
{
    if (!r) return 0;
    if (!r->left && !r->right) return 1;
    return countLeaves(r->left) + countLeaves(r->right);
}

int main(void)
{
    /*
            1
          /   \
         2     3
        / \     \
       4   5     6
    */
    struct TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Height : %d\n", height(root));
    printf("Nodes  : %d\n", countNodes(root));
    printf("Leaves : %d\n", countLeaves(root));
    return 0;
}
