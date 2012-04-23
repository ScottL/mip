#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct min_priority_queue *min_pq;

min_pq create_min_pq(int);
Key min(min_pq);
//void resize(min_pq, int);			// doesn't need to be in the header
Key min(min_pq);
void insert(min_pq, Key);
Key del_min(min_pq);
