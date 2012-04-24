#include "minpikaqueue.h"

struct min_priority_queue {
				int size;
				int num;
				item *items;
    int (*compare)(const void *a, const void *b);
};

void swap(min_pq, int, int);
void swim(min_pq, int);
void sink(min_pq, int);

min_pq create_min_pq(int n, int (*com)(const void *a, const void *b)) {
				min_pq mpq = malloc(sizeof(min_pq));
				mpq->items = malloc(sizeof(char *) * (n + 1));
				mpq->size = n;
				mpq->num = 0;
    mpq->compare = com;
				return mpq;
}

item min(min_pq m) {
				if (m->num == 0) return NULL;
				return m->items[1];
}

void resize_min_pq(min_pq m, int new_size) {
				realloc(m->items, sizeof(char *) * (new_size + 1));
}

void insert(min_pq m, item item) {
				if (m->size - 1 == m->num)
								resize_min_pq(m, 2 * m->size);
				m->items[++(m->num)] = item;
				swim(m, m->num);
}

item del_min(min_pq m) {
				if (m->num == 0) return NULL;
				swap(m, 1, m->num);
				item min = m->items[m->num--];
				sink(m, 1);
}

void swap(min_pq m, int a, int b) {
				item temp = m->items[a];
				m->items[a] = m->items[b];
				m->items[b] = temp;
}

void swim(min_pq m, int n) {
				while (n > 1 && greater(m, n / 2, n)) {
        swap(m, n, n / 2);
        n = n / 2;
    }
}

void sink(min_pq m, int n) {
    while (2 * n <= m->num) {
        int j = 2 * n;
        if (j < m->num && greater(m, j, j + 1)) j++;
        if (!greater(n, j)) break;
        swap(m, n, j);
        n = j;
    }
}

int greater(min_pq m, int a, int b) {
    return m->compare(m->items[a], m->items[b]);
}

#ifdef DEBUG
void print_min_pq(min_pq m, char (*to_string)(void *p), char *s) {
    min_pq temp = malloc(sizeof(m));
    memcpy(temp, m, sizeof(m));
    printf("\n***************printing %s priority queue****************\n", s);
    while (temp->num > 0) {
        item t = del_min(temp);
        printf("%s\n", to_string(t));
    }
    printf("*********************************************************\n\n");
}
#endif
