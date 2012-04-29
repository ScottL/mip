#include "sandslhash.h"

struct sandslhash {
				int N;
				int M;	//size of linear probing table
				Key *keys;
				Val *vals;
};

hash_table create_hash_table(int size) {
				hash_table h = malloc(sizeof(struct sandslhash));
				h->M = size; //??????????????????
				h->N = 0;
				h->keys = malloc(sizeof(void *) * size);
				h->vals = malloc(sizeof(void *) * size);
				return h;
}

int hash_code(hash_table, Key);

bool contains(hash_table h, Key key) { return get(h, key) != NULL; }

int hash(hash_table h, Key key) { return (hash_code(h, key) & 0x7fffffff) % h->M; }

int hash_code(hash_table h, Key key) {
				int hsh = 0;
				//char *ptr = key;
				//for (ptr = key; ptr != '\0'; ptr++) hsh += *ptr + (31 * hsh);
				int i;
				for (i = 0; i < strlen(key); i++) hsh += key[i] + (31 * hsh);
				return hsh;
}

void resize_hash(hash_table h, int size) {
				printf("resizing hash table...\n");
				hash_table hold = create_hash_table(size);
				int i;
				for (i = 0; i < h->M; i++) {
								if (h->keys[i] != NULL) {
												put(hold, h->keys[i], h->vals[i]);
								}
				}
				realloc(h->keys, sizeof(void *) * size);
				realloc(h->vals, sizeof(void *) * size);
				for (i = 0; i < size; i++) {
								h->keys[i] = hold->keys[i];
								h->vals[i] = hold->vals[i];
				}
				h->M = hold->M;
}

void put(hash_table h, Key key, Val val) {
				if (val == NULL) remove(key);
				if (h->N >= h->M / 2) resize_hash(h, 2 * (h->M));
				int i;
				for (i = hash(h, key); h->keys[i] != NULL; i = (i + 1) % h->M) {
								if (strcmp(h->keys[i], key) == 0) {
												h->vals[i] = val;
												return;
								}
				}
				h->keys[i] = key;
				h->vals[i] = val;
				(h->N)++;
}

Val get(hash_table h, Key key) {
				int i;
				for (i = hash(h, key); h->keys[i] != NULL; i = (i + 1) % h->M)
								if (strcmp(h->keys[i], key) == 0)
												return h->vals[i];
    return NULL;
}

void del_key(hash_table h, Key key) {
				if (!contains(h, key)) return;
				int i = hash(h, key);
				while (strcmp(h->keys[i], key) != 0) {
								i = (i + 1) % h->M;
				}

				h->keys[i] = NULL;
				h->vals[i] = NULL;

				i = (i + 1) % h->M;
				while (h->keys[i] != NULL) {
								Key key_rehash = h->keys[i];
								Val val_rehash = h->vals[i];
								h->keys[i] = NULL;
								h->vals[i] = NULL;
								(h->N)--;
								put(h, key_rehash, val_rehash);
								i = (i + 1) % h->M;
				}

				(h->N)--;

				if (h->N > 0 && h->N <= (h->M / 8)) resize_hash(h, h->M / 2);
}

void print_hash_table(hash_table h) {
				int i;
				printf("\n\t\tonline pool:\n");
				for (i = 0; i < h->M; i++) {
								printf("%s %s\n", h->keys[i], h->vals[i]);
				}
				printf("------------------------------\n\n");
}
