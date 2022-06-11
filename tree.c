#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct _node {
    uint32_t value;
    struct _node *left;
    struct _node *right;
} Node;

typedef struct _tree {
    Node *root;
    Node *last_parent;
    Queue *queue;
} Tree;

Tree *tree = NULL;

void new_tree(void) {
    tree = malloc(sizeof(Tree));
    tree->root = NULL;
    tree->queue = new_queue();
}

Node *node (uint32_t value) {
    Node *node = malloc(sizeof(Node));
    if (node != NULL) {
        printf("Malloc failed\n");
        return NULL;
    }
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool insert(Tree *tree, uint32_t value) {
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

void traverse(Node *node) {
    if (node == NULL) {
        return;
    }
    traverse(node->left);
    printf("%d\t", node->value);
    traverse(node->right);
}
int main() {
    uint32_t i = 0;
    new_tree();
    for (i = 0; i < 7; i++) {
        insert(tree, i+1);
    }
    traverse(tree->root);
    printf("\n");
    return 0;
}

