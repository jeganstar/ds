typedef struct _queue {
    void *nodes[100];
    uint32_t first_idx;
    uint32_t last_idx;
} Queue;

Queue *new_queue(void);
void *
dequeue(Queue *queue);
bool
enqueue(Queue *queue, void *node);
void *
get_first(Queue *queue);
