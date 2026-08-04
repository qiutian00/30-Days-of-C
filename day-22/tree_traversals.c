#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *newNode(int data)
{
    struct TreeNode *n = malloc(sizeof(*n));
    n->data  = data;
    n->left = n->right = NULL;
    return n;
}

void preorder(struct TreeNode *r)
{
    if (!r) return;
    printf("%d ", r->data);
    preorder(r->left);
    preorder(r->right);
}

void inorder(struct TreeNode *r)
{
    if (!r) return;
    inorder(r->left);
    printf("%d ", r->data);
    inorder(r->right);
}

void postorder(struct TreeNode *r)
{
    if (!r) return;
    postorder(r->left);
    postorder(r->right);
    printf("%d ", r->data);
}

/*
        1
      /   \
     2     3
    / \     \
   4   5     6
*/
int main(void)
{
    struct TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Pre-order : ");
    preorder(root);
    printf("\n");

    printf("In-order  : ");
    inorder(root);
    printf("\n");

    printf("Post-order: ");
    postorder(root);
    printf("\n");

    return 0;
}
