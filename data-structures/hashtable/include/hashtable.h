#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>




typedef struct HashTable HashTable;
typedef struct hashtable_operations hashtable_operations;

struct HashTable {
  
  void (*init) (HashTable* self, size_t hashtable_size);
  // Destroys all internally malloced properties.  
  void (*destroy) (HashTable* self);
  const hashtable_operations* methods;
  size_t private_size;
  size_t entries;
  void** H;
};

struct hashtable_operations {
  void (*insert) (HashTable* self, char key[], size_t key_length, void* value);
  void* (*get) (HashTable* self, char key[], size_t key_length);
  void (*remove) (HashTable* self, char key[], size_t key_length);
};


void hashtable_init(HashTable* self, size_t hashtable_size);
void hashtable_destroy(HashTable* self);

#endif
