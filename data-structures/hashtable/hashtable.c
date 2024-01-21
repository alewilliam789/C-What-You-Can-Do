#include <assert.h>
#include <stdbool.h>
#include "hashtable.h"

void hashtable_copy(void** new_table, void** previous_table, size_t previous_size){
  size_t i = 0;
  while(i < previous_size){
    new_table[i] = previous_table[i];
    i++;
  }
}

int hash_key(char string[], size_t string_length, size_t table_size) {
  int hash = 0;
  size_t i = 0;

  assert(string_length > 0);

  while (i <= string_length-1) {
    // SDBM Hash Function
    hash += (hash << 6) + (hash << 16) - hash + string[i];
    i++;
  }
  return hash % table_size;
}


void hashtable_insert (HashTable *self, char key[], size_t key_length, void* value) {
  if(self->entries+1 <= self->private_size) {
    int hash_index = hash_key(key, key_length, self->private_size);
    self->H[hash_index] = value;
    self->entries++;
  }
  else {
    size_t previous_size = self->private_size;
    self->private_size = (3*self->private_size)/2;
    void** new_table = malloc(sizeof(value)* self->private_size);
    hashtable_copy(new_table, self->H, previous_size);
    free(self->H);
    self->H = new_table;
  }
}

 void* hashtable_get (HashTable *self, char key[], size_t key_length) {
  
  assert(key_length > 0);
  int hash_index = hash_key(key,key_length, self->private_size);

  if(self->H[hash_index]) {
    return self->H[hash_index];
  }
  else {
    return NULL;
  }
}

void hashtable_remove (HashTable *self, char key[], size_t key_length) {
  assert(key_length > 0);

  int hash_index = hash_key(key, key_length, self->private_size);
  self->H[hash_index] = NULL;
  self->entries--;
}

static const hashtable_operations hashtable_methods = {
  .get = hashtable_get,
  .insert = hashtable_insert,
  .remove = hashtable_remove
};



void hashtable_init(HashTable *self, size_t hashtable_size) {

  assert (hashtable_size > 0);

  // If hashtable_size is the length of the data you are storing, then pass the size of the data and hashtable will never be loaded more than 2/3
  self->private_size = (3*hashtable_size)/2;

  self->methods = &hashtable_methods;

  self->H = malloc(sizeof(void*) * self->private_size);
  
  self->entries = 0;
  
  size_t i = 0;
  while (i < self->private_size) {
    self->H[i] = NULL;
    i++;
  }
}

void hashtable_destroy(HashTable *self) {
  free(self->H);
}
