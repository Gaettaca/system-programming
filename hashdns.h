#ifndef _CDNS_HASHDNS_H_
#define _CDNS_HASHDNS_H_

#include <string.h>
#include <stdlib.h>

#define DOCTOR_WHO 10-0-11-0-0:0-2
#define SIZE 20000

typedef struct Node {
    char *domain;
    char *ip;
    unsigned int key_size;

    struct Node *next;
} Node;


typedef struct HashTable {
    Node ** array;
    unsigned int arraySize;
} HashTable;

//  Robert Sedgewick's hash-function - the simplest one in the known Universe.
unsigned int RSHashFunc(const char* ip);

HashTable *HashTableInit();

char *HashTableSearch(HashTable *hashTable, char *domain);

void HashTableInsert(HashTable *hashTable, char *domain, char *ip);

void HashTableRemove(HashTable *hashTable);

#endif //CDNS_HASHDNS_H
