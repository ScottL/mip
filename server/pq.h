#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct min_priority_queue *min_pq;

min_pq create_min_pq(void);
Key min(min_pq);
void resize(min_pq);			// doesn't need to be in the header

