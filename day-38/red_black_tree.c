#include <stdio.h>
#include <stdlib.h>

#define RED   0
#define BLACK 1

struct Node {
    int key;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *rb_new(int key) {
    struct Node *n = malloc(sizeof(*n));
    n->key = key; n->color = RED;
    n->left = n->right = n->parent = NULL;
    return n;
}

void left_rotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;

    if (!x->parent) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void right_rotate(struct Node **root, struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;

    if (!x->parent) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void rb_fixup(struct Node **root, struct Node *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node *uncle = z->parent->parent->right;
            if (uncle && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(root, z->parent->parent);
            }
        } else {
            struct Node *uncle = z->parent->parent->left;
            if (uncle && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rb_insert(struct Node **root, int key) {
    struct Node *z = rb_new(key);
    struct Node *y = NULL, *x = *root;

    while (x) { y = x; x = (z->key < x->key) ? x->left : x->right; }
    z->parent = y;
    if (!y) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    rb_fixup(root, z);
}

struct Node *rb_search(struct Node *root, int key) {
    while (root && root->key != key)
        root = (key < root->key) ? root->left : root->right;
    return root;
}

void rb_inorder(struct Node *root) {
    if (!root) return;
    rb_inorder(root->left);
    printf("%d(%c) ", root->key, root->color == RED ? 'R' : 'B');
    rb_inorder(root->right);
}

int rb_height(struct Node *root) {
    if (!root) return 0;
    int l = rb_height(root->left), r = rb_height(root->right);
    return (l > r ? l : r) + 1;
}

int main(void) {
    struct Node *root = NULL;
    int keys[] = {10, 20, 30, 15, 25, 5, 1};

    for (int i = 0; i < 7; i++) rb_insert(&root, keys[i]);

    printf("in-order: ");
    rb_inorder(root);
    printf("\nheight = %d\n", rb_height(root));

    printf("search 15 -> %s\n", rb_search(root, 15) ? "found" : "not found");
    printf("search 99 -> %s\n", rb_search(root, 99) ? "found" : "not found");

    return 0;
}
