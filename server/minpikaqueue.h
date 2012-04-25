#include "mip.h"

typedef struct min_priority_queue *min_pq;

typedef void *item;

min_pq create_min_pq(int, int (*compare)(const void *, const void *));
item min(min_pq);
//void resize(min_pq, int);			// doesn't need to be in the header
item min(min_pq);
void insert(min_pq, item);
item del_min(min_pq);
void print_min_pq(min_pq, char *(string_func)(void *p), char *s);
