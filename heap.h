#include "common.h"

#define MAX_HEAP_SIZE 50

typedef enum options {
    MIN,
    MAX
} options_e;

typedef struct heap_node {
    uint32_t sort_key;
    void *data_node;
} heapNode;

typedef struct _heap {
    uint32_t max_heap_size;
    uint32_t heap_size;
    options_e opt;
    heapNode **nodes;
} Heap;
int create_heap(uint32_t heap_size);

void
heap_sort(Heap *heap);
