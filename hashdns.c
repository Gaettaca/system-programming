#include "hashdns.h"

unsigned int RSHash(const char *domain) {
    unsigned int b    = 378551;
    unsigned int a    = 63689;
    unsigned int hash = 0;

    for(; *domain; ++domain) {
        hash = hash * a + *domain;
        a = a * b;
    }

    return hash;
}

HashTable *HashTableInit() {
    HashTable *hashTable = (HashTable *) malloc(sizeof(HashTable));
    hashTable->arraySize = SIZE;
    hashTable->array = calloc(hashTable->arraySize, sizeof(**(hashTable->array)));

    for (unsigned int i = 0; i < hashTable->arraySize; ++i) {
        hashTable->array[i] = NULL;
    }

    return hashTable;
}

char *HashTableSearch(HashTable *hashTable, char *key) {
    unsigned int key_length = strlen(key);

    unsigned int index = RSHash(key) % hashTable->arraySize;
    if (hashTable->array[index] == NULL) {
        return NULL;
    }
    Node *node = hashTable->array[index];
    while (node != NULL) {
        if (node->key_size == key_length) {
            if (!strcmp(key, node->domain)) {
                return node->ip;
            }
        }
        node = node->next;
    }
    return NULL;
}

void HashTableInsert(HashTable *hashTable, char *key, char *value) {
    unsigned key_length = strlen(key);
    unsigned value_length = strlen(value);

    unsigned int index = RSHash(key) % hashTable->arraySize;
    Node *node, *last_node;
    node = hashTable->array[index];
    last_node = NULL;

    while (node != NULL) {
        last_node = node;
        if (!strcmp(last_node->domain, key)){
            break;
        }
        node = node->next;
    }

    Node *new_node;
    new_node = malloc(sizeof(Node));
    new_node->domain = malloc(key_length);
    new_node->ip = malloc(value_length);
    strcpy(new_node->domain, key);
    strcpy(new_node->ip, value);
    new_node->key_size = key_length;
    new_node->next = NULL;

    if (last_node != NULL) {
        last_node->next = new_node;
    } else {
        hashTable->array[index] = new_node;
    }
}

void HashTableRemove(HashTable *hashTable){
    for (unsigned int index = 0; index < SIZE; ++index){
        Node *node = hashTable->array[index];
        Node *next_node = NULL;
        while (node != NULL){
            next_node = node->next;
            free(node->domain);
            free(node->ip);
            free(node->next);
            free(node);
            node = next_node;
        }
        free(hashTable->array[index]);
    }
    free(hashTable);
}