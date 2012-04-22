#include "sandslhash.h"

struct sandslhash {
				int size;
				int M;	//size of linear probing table
				Key keys[4];
				Val vals[4];
};

hash create(void) {
				hash h = malloc(sizeof(struct sandslhash));
				h->M = 100; //THIS IS HIGHLY UNQUESTIONABLE! no evidence i.e citation needed
				h->size = 4;
				return h;
}

bool contains(hash, Key key) {
				return get(hash, key) == NULL;
}

int HASH(hash h, Key key) {
				return (hash_code(h, key) & 0x7fffffff) % h->M;
}

int hash_code(hash h, Key key) {
				int hsh = 0;
				char *ptr = key;
				for (ptr = key; ptr != '\0'; ptr++)
								hsh += *ptr + (31 * hsh);
				return hsh;
}

void resize(hash h) {

}

void put(hash h, Key key, Val val) {
				if (val == NULL) remove(key);
				if (N >= M / 2) resize(2 * M);
				int i;
				for (i = HASH(key); h->keys[i] != NULL; i = (i + 1) % h->M) {
								if (strcmp(h->keys[i], key) == 0) {
												h->vals[i] = val;
												return;
								}
				}
				h->keys[i] = key;
				h->vals[i] = val;
				(h->N)++;
}

Val get(hash h, Key key) {
				int i;
				for (i = HASH(h, key); h->keys[i] != NULL; i = (i + 1) % M)
								if (strcmp(h->keys[i], key) == 0)
												return h->vals[i];
}

void remove(hash h, Key key) {
				if (!contains(h, key)) return;
				int i = HASH(h, key);
}
