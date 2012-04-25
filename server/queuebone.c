/** server request queue **/
/** multiple queuebones should be used to handle different requests **/

#include "mip.h"
#include "queuebone.h"

struct queue {
    int size;
    QNODE *first;
    QNODE *last;
};

struct node {
    char *ptr;
    struct node *next;
};

int size(request_queue q) {
    return q->size;
}

request_queue create_queue(void) {
    request_queue q = malloc(sizeof(struct queue));
    if (q == NULL)
        printf("error: queue not created\n");
    q->size = 0;
    return q;
}

int init(request_queue q, char *p) {
    q->first = malloc(sizeof(QNODE));
    q->last = malloc(sizeof(QNODE));
    if (q->first == NULL || q->last == NULL)
        return -1;
    q->first->ptr = p;
    q->first->next = NULL;
    q->size++;
    return 0;
}

int enqueue(request_queue q, char *p) {
    printf("***enqueueing %s***\n", (char *)p);
    if (q->size == 0)
        return init(q, p);
    QNODE *n = malloc(sizeof(QNODE));
    n->ptr = p;
    n->next = NULL;
    if (q->size == 1) {
        q->last = n;
        q->first->next = n;
    }
    else {
        q->last->next = n;
        q->last = n;
    }
    q->size++;
}

char *dequeue(request_queue q) {
    QNODE *ret = malloc(sizeof(QNODE));
    ret = q->first;
    q->first = q->first->next;
    q->size--;
    return ret->ptr;
}

#ifdef DEBUG
void printq(request_queue q, char *tag) {
    printf("\n\t\tCURRENT %s QUEUE\n", tag);
    printf("queue size: %d\n", q->size);
    if (q->size == 0) {
        printf("queue is empty..\n\n");
        return;
    }
    printf("-------------------------------------------------------\n");
    QNODE *n = malloc(sizeof(QNODE));
    n = q->first;
    int i;
    for (i = 0; i < q->size; i++) {
        printf("%s\n", (char *)(n->ptr));
        n = n->next;
    }
    printf("-------------------------------------------------------\n\n");
}
#endif
