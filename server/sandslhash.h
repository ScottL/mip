#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mip.h"
typedef struct sandslhash *hash_table;
typedef char * Key;
typedef char * Val;

hash_table create_hash_table(int);
bool contains(hash_table, Key);
int hash(hash_table, Key);
//void resize(hash_table, int);
void put(hash_table, Key, Val);
Val get(hash_table, Key);
void del_key(hash_table, Key);
void print_hash_table(hash_table);
