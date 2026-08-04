#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int key)
{
    struct Node *n = malloc(sizeof(*n));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

struct Node *insert(struct Node *root, int key)
{
    if (!root) return newNode(key);
    if (key < root->key)      root->left  = insert(root->left,  key);
    else if (key > root->key) root->right = insert(root->right, key);
    return root;
}

struct Node *search(struct Node *root, int key)
{
    if (!root)            return NULL;
    if (key == root->key) return root;
    if (key <  root->key) return search(root->left,  key);
    return search(root->right, key);
}

struct Node *minNode(struct Node *r)
{
    while (r->left) r = r->left;
    return r;
}

struct Node *delete(struct Node *root, int key)
{
    if (!root) return NULL;
    if (key < root->key)      root->left  = delete(root->left,  key);
    else if (key > root->key) root->right = delete(root->right, key);
    else {
        if (!root->left)  { struct Node *c = root->right; free(root); return c; }
        if (!root->right) { struct Node *c = root->left;  free(root); return c; }
        struct Node *succ = minNode(root->right);
        root->key = succ->key;
        root->right = delete(root->right, succ->key);
    }
    return root;
}

void inorder(struct Node *r)
{
    if (!r) return;
    inorder(r->left);
    printf("%d ", r->key);
    inorder(r->right);
}

int main(void)
{
    struct Node *root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) root = insert(root, keys[i]);

    printf("In-order : ");
    inorder(root);
    printf("\n");

    struct Node *f = search(root, 40);
    printf("Search 40: %s\n", f ? "found" : "not found");

    root = delete(root, 30);
    printf("After del 30: ");
    inorder(root);
    printf("\n");
    return 0;
}
