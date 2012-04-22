#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct sandslhash *hash;
typedef char * Key;
typedef char * Val;

hash create(void);
bool contains(hash, Key);
int hash(hash, Key);
void resize(hash);
void put(hash, Key, Val);
char *get(hash, Key);
void remove(hash, Key);
