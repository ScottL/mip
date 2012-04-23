#include "minpikaqueue.h"

struct min_priority_queue {
				int size;
				int num;
				Key keys[0];
};

min_pq create_min_pq(int n) {
				min_pq mpq = malloc(sizeof(min_pq));
				realloc(mpq->keys, sizeof(char *) * (n + 1));
				mpq->size = n;
				mpq->num = 0;
				return mpq;
}

Key min(min_pq m) {
				if (m->num == 0) return NULL;
				return m->keys[1];
}

void resize(min_pq m, int new_size) {
				realloc(m->keys, sizeof(char *) * (new_size + 1));
}

void insert(min_pq m, Key key) {
				if (m->size - 1 == m->num)
								resize(m, 2 * m->size);
				m->keys[++(m->num)] = x;
				swim(m, m->num);
}

Key del_min(min_pq m) {
				if (m->num == 0) return NULL;
				swap(m, 1, m->num);
				Key min = m->keys[m->num--];
				sink(m, 1);
}

void swap(min_pq m, int a, int b) {
				Key temp = m->keys[a];
				m->keys[a] = m->keys[b];
				m->keys[b] = temp;
}

void sink(min_pq m, int n) {
				while (n > 1 && 
}
