#include "heap.h"
void
print_array(Heap *heap, uint32_t heap_size) {
    int32_t i =0;
    heapNode **nodes = heap->nodes;
    for (i =0; i< heap_size; i++) {
        printf("%d\t", nodes[i]->sort_key);
    }
    printf("\n");
}
int8_t compare(uint32_t val1, uint32_t val2, options_e opt) {
    printf("compare value %d, %d\n", val1, val2);
    if (val1 > val2) {
        return ((opt == MAX) ? 1 : -1);
    } else if (val1 < val2) {
        return ((opt == MAX) ? -1 : 1);
    } else {
        return 0;
    }
}
bool limit_check(Heap *heap, uint32_t index) {
    if (index > heap->heap_size - 1 || index < 0) {
        return false;
    }
    return true;
}
int32_t parent (int index) {
    return ((index - 1) / 2);
}


uint32_t left (uint32_t index) {
    return ((2 * index) + 1);
}

uint32_t right (uint32_t index) {
    return ((2 * index) + 2);
}

int32_t fair_child (Heap *heap, uint32_t index) {
    uint32_t left_idx = left(index);
    uint32_t right_idx = right(index);
    int8_t diff = 0;
    printf("compare %d, %d\n", left_idx, right_idx);
    if (limit_check(heap, left_idx) == false && limit_check(heap, right_idx) == false) {
        return -1;
    }
    
    if (limit_check(heap, right_idx) == false && limit_check(heap, left_idx) == true) { 
        return left_idx;
    }

    diff = compare(heap->nodes[left_idx]->sort_key,
                 heap->nodes[right_idx]->sort_key, heap->opt);

    if (diff > 0) {
        return left_idx;
    } else if (diff < 0) {
        return right_idx;
    } else {
        return left_idx;
    }
}

void swap(Heap *heap, uint32_t index1, uint32_t index2) {
    heapNode *tmp = NULL;

    tmp = heap->nodes[index1];
    heap->nodes[index1] = heap->nodes[index2];
    heap->nodes[index2] = tmp;
}

void heapify (Heap *heap, uint32_t index) {
    int32_t gc_index = 0;
    int8_t diff = 0;
    
    gc_index = fair_child(heap,index);
    if (gc_index < 0) {
        return;
    }
    printf("Fair child %d\n", gc_index);
    
    diff = compare(heap->nodes[index]->sort_key, 
                heap->nodes[gc_index]->sort_key, heap->opt);
    if (diff < 0) {
        swap(heap, index, gc_index);
        heapify(heap, gc_index);
    }
    
}

void
bubble_up(Heap *heap, uint32_t index) {
    uint32_t parent_idx = parent(index);
    int8_t diff = 0;
    
    if(limit_check(heap, parent_idx) == false) {
        return;
    }
    
    diff = compare(heap->nodes[parent_idx]->sort_key, 
            heap->nodes[index]->sort_key, heap->opt);
    if (diff < 0) {
        swap(heap, parent_idx, index);
        bubble_up(heap, parent_idx);
    }

    
}
void insert (Heap *heap, heapNode *value, options_e opt) {
    /*insert at the end */
    if (heap->heap_size >= MAX_HEAP_SIZE) {
        printf("cannot be inserted, reached max limit");
        return;
    }

    heap->nodes[heap->heap_size] = value;
    heap->heap_size++;
    printf("Inserting value %d, new heap_size %d\n", 
        heap->nodes[heap->heap_size]->sort_key, heap->heap_size);
    bubble_up(heap, heap->heap_size - 1);
}

heapNode* get(Heap *heap) {
    heapNode *pri = heap->nodes[0];
    swap(heap, 0, heap->heap_size - 1);
    heap->heap_size--;

    heapify(heap, 0);
    return pri;
}

void
heap_sort(Heap *heap) {
    uint32_t i = 0;
    uint32_t size = heap->heap_size;
    printf("Heap sort of size %d\n", size);
    for(i = 0; i <  size - 1; i++) {
        get(heap);
    print_array(heap, size);
    }
}

int create_heap(uint32_t heap_size)
{
    int32_t i = 0;
    Heap *heap = malloc(sizeof(Heap));
    if (heap == NULL) {
        printf("Heap creation failed\n");
        return -1;
    }
    memset(heap, 0, sizeof(Heap));

    heap->nodes = (heapNode **)malloc(heap_size * sizeof(heapNode *));
    if (heap->nodes == NULL) {
        printf("Heap node creation failed\n");
        free(heap);
        return -1;
    }
    for (i = 0; i < heap_size; i++) {
        heap->nodes[i] = (heapNode *)malloc(sizeof(heapNode));
        memset(heap->nodes[i], 0, sizeof(heapNode));
    }
    heap->max_heap_size = heap_size;

    printf("heap size %d\n", heap_size);
    print_array(heap, heap_size);
    for (i = heap_size - 1; i > -1; i--) {
        heapify(heap, i);
    }
    return heap;
    
/*
    uint32_t size = 0;
    if (heap_size >= MAX_HEAP_SIZE) {
        return -1;
    }
    heap_size = l_heap_size;
    print_array(arr, heap_size);
    insert(10, opt);
    print_array(arr, heap_size);
    size = heap_size;
    heap_sort(opt, size);
    print_array(arr, size);
*/
}
