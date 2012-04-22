#include "sandslhash.h"

struct sandslhash {
				int size;
				int M;	//size of linear probing table
				Key keys[4];
				Val vals[4];
};

hash create(void) {
				hash h = malloc(sizeof(struct sandslhash));
				h->M = 5; //THIS IS HIGHLY UNQUESTIONABLE! no evidence i.e citation needed
				h->size = 4;
				return h;
}

bool contains(hash, Key key) {
				return get(hash, key) == NULL;
}

int hash(Key key) {
				return (
}
