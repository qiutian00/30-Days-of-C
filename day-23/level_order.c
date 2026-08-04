#include <stdio.h>
#include <stdlib.h>

#define MAXQ 128

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

void levelorder(struct TreeNode *root)
{
    if (!root) return;
    struct TreeNode *q[MAXQ];
    int head = 0, tail = 0;
    q[tail++] = root;

    while (head != tail) {
        struct TreeNode *cur = q[head++];
        printf("%d ", cur->data);
        if (cur->left)  q[tail++] = cur->left;
        if (cur->right) q[tail++] = cur->right;
    }
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

    printf("Level-order: ");
    levelorder(root);
    printf("\n");
    return 0;
}
