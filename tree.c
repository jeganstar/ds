#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#define max(a, b)  (((int32_t)a > (int32_t)b) ?a :b)
#define min(a, b)  (((int32_t)a < (int32_t)b) ?a :b)

typedef struct _node {
    uint32_t value;
    uint32_t height;
    struct _node *left;
    struct _node *right;
} Node;

typedef struct _tree {
    Node *root;
    Node *last_parent;
    Queue *queue;
} Tree;


Tree* new_tree(void) {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->queue = new_queue();
    return (tree);
}

Node *node (uint32_t value) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        printf("Malloc failed\n");
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 0;
    return node;
}
uint32_t insert_internal(Node *root, uint32_t value) {
        uint32_t height = 0;
        if (value < root->value ) {
            if (root->left == NULL) {
                root->left = node(value);
                root->height++;
                return root->height;
            } else {
                height = insert_internal(root->left, value);
                root->height = 1 + max(height,
                                ((root->right) ? root->right->height: -1));
                return root->height;
            }
        } else if (value > root->value) {
            if (root->right == NULL) {
                root->right = node(value);
                root->height++;
                return root->height;
            } else {
                height = insert_internal(root->right, value);
                root->height = 1 + max(height,
                                ((root->left) ? root->left->height: -1));
                return root->height;
            }
        } else {
            printf("Duplicate value \n");
            return root->height;
        }
}

Node* search_internal(Node *root, uint32_t value) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root->value) {
        return search_internal(root->left, value);
    } else if (value > root->value) {
        return search_internal(root->right, value);
    } else {
        return root;
    }
}
Node * search(Tree *tree, uint32_t value) {
    if (tree->root == NULL) {
        printf("Tree is empty");
        return NULL;
    } else {
        return search_internal(tree->root, value);
    }
}

uint32_t insert_bst (Tree *tree,  uint32_t value) {
    if (tree->root == NULL) {
        tree->root = node(value);
        return tree->root->height;
    } else {
        return insert_internal(tree->root, value);
    }
}

bool insert_bfs(Tree *tree, uint32_t value) {
    if (tree == NULL) {
        printf("Tree is NULL\n");
        return false;
    }

    if (node == NULL) {
        printf("Node is NULL\n");
        return false;
    }
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = value;

    if (tree->root == NULL) {
        tree->root = node;
        enqueue(tree->queue, (void *)node);
        return true;
    } else {
        if (tree->queue != NULL) {
            Node *last_parent = (Node *)get_first(tree->queue);
            if (last_parent->left == NULL) {
                last_parent->left = node;
                enqueue(tree->queue, (void *)node);
            } else {
                last_parent->right = node;
                dequeue(tree->queue);
                enqueue(tree->queue, (void *)node);
            }
        } else {
            printf("Last parent is NULL\n");
        }
    }
}

static int32_t
height_internal (Node *node) {
    if (node == NULL) {
        return -1;
    }
    node->height = 1 + max(height_internal(node->left), 
        height_internal(node->right));
    return node->height;
}

uint32_t height(Tree *tree) {
    return (height_internal(tree->root));
}

void traverse(Node *node) {
    if (node == NULL) {
        return;
    }
    traverse(node->left);
    printf("%d\t", node->value);
    traverse(node->right);
}

/*
uint32_t balance_internal(Node *root) {
    int32_t l_height = 0, r_height =0;
    int32_t
    if (root == NULL) {
        return 0;
    }
    l_height = balance_internal(root->left);
    r_height = balance_internal(root->right);

    balance = l_height - r_height;
    if ((int32_t)(balance) >= 2 ) {
    } 
    if (int32_t)(balance) <= -2) {
    }
        balance(root); 
    }
    return (1 + max(l_height, r_height));
}
bool balance(Tree *tree) {
    if (tree->root == NULL) {
        printf("Tree is empty\n")
        return false;
    }
    return balance_internal(tree->root);
}
*/
int main() {
    Tree *tree = NULL;
    tree = new_tree();
    insert_bst(tree, 1);
    
    printf("Height of tree %d\n", insert_bst(tree, 2));
    printf("Height of tree %d\n", insert_bst(tree, 8));
    printf("Height of tree %d\n", insert_bst(tree, 10));
    printf("Height of tree %d\n", insert_bst(tree, 3));
    printf("Height of tree %d\n", insert_bst(tree, 5));
    traverse(tree->root);
    printf("\n");
    printf((search(tree, 100) == NULL) ? "Not Found\n":"Found\n");
    return 0;
}

