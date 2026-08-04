#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int key;
    int height;
    struct AVLNode *left, *right;
};

static int h(struct AVLNode *n) { return n ? n->height : 0; }
static int maxi(int a, int b)   { return a > b ? a : b; }

static void updateH(struct AVLNode *n) { n->height = 1 + maxi(h(n->left), h(n->right)); }
static int  bf(struct AVLNode *n)      { return n ? h(n->left) - h(n->right) : 0; }

static struct AVLNode *rightRotate(struct AVLNode *z)
{
    struct AVLNode *y = z->left;
    struct AVLNode *T3 = y->right;

    y->right = z;
    z->left  = T3;

    updateH(z);
    updateH(y);
    return y;
}

static struct AVLNode *leftRotate(struct AVLNode *z)
{
    struct AVLNode *y = z->right;
    struct AVLNode *T2 = y->left;

    y->left  = z;
    z->right = T2;

    updateH(z);
    updateH(y);
    return y;
}

static struct AVLNode *newNode(int key)
{
    struct AVLNode *n = malloc(sizeof(*n));
    n->key = key; n->height = 1;
    n->left = n->right = NULL;
    return n;
}

struct AVLNode *insert(struct AVLNode *n, int key)
{
    if (!n) return newNode(key);
    if      (key < n->key) n->left  = insert(n->left,  key);
    else if (key > n->key) n->right = insert(n->right, key);
    else return n;

    updateH(n);
    int b = bf(n);

    if (b > 1 && key < n->left->key)
        return rightRotate(n);
    if (b < -1 && key > n->right->key)
        return leftRotate(n);
    if (b > 1 && key > n->left->key) {
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    if (b < -1 && key < n->right->key) {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}

static void preorder(struct AVLNode *r)
{
    if (!r) return;
    printf("%d(h=%d) ", r->key, r->height);
    preorder(r->left);
    preorder(r->right);
}

int main(void)
{
    struct AVLNode *root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        root = insert(root, keys[i]);
        printf("After inserting %2d: ", keys[i]);
        preorder(root);
        printf("\n");
    }
    return 0;
}
