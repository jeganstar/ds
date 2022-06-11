#include "heap.h"

int main() {
    Heap *heap = create_heap(50, MIN);
    insert(heap, 20, NULL);
    insert(heap, 19, NULL);
    insert(heap, 8, NULL);
    insert(heap, 10, NULL);
    insert(heap, 1, NULL);
    insert(heap, 2, NULL);
    insert(heap, 3, NULL);
    printf("%d\n", get(heap)->sort_key);
}
