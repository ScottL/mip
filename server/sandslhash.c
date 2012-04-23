#include "sandslhash.h"

struct sandslhash {
				int N;
				int M;	//size of linear probing table
				Key keys[4];
				Val vals[4];
};

hash_table create_hash_table(void) {
				hash_table h = malloc(sizeof(struct sandslhash));
				h->M = 100; //THIS IS HIGHLY UNQUESTIONABLE! no evidence i.e citation needed
				h->N = 4;
				return h;
}

bool contains(hash_table h, Key key) { return get(h, key) == NULL; }

int hash(hash_table h, Key key) { return (hash_code(h, key) & 0x7fffffff) % h->M; }

int hash_code(hash_table h, Key key) {
				int hsh = 0;
				char *ptr = key;
				for (ptr = key; ptr != '\0'; ptr++) hsh += *ptr + (31 * hsh);
				return hsh;
}

void resize(hash_table h, int size) {

}

void put(hash_table h, Key key, Val val) {
				if (val == NULL) remove(key);
				if (h->N >= h->M / 2) resize(h, 2 * (h->M));
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

				if (h->N > 0 && h->N <= (h->M / 8)) resize(h, h->M / 2);
}
