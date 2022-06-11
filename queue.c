#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


Queue *queue = NULL;

bool
enqueue(Queue *queue, void *node) {
    if (queue->last_idx < 100 -1) {
        queue->nodes[queue->last_idx++] = node;
        return true;
    }
    return false;
}

void *
dequeue(Queue *queue) {
    if (queue->first_idx < queue->last_idx) {
        return queue->nodes[queue->first_idx++];
    }
    return NULL;
}

void *
get_first(Queue *queue) {
    if (queue->first_idx < queue->last_idx) {
        return queue->nodes[queue->first_idx];
    }
    return NULL;
}

Queue * new_queue(void) {
    queue = malloc(sizeof(Queue));
    memset(queue, 0, sizeof(Queue));
    return queue;
}
