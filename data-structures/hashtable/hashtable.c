#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashtable.h"


int hash_key(char string[], unsigned int string_length, unsigned int table_size) {
  unsigned int hash = 0;
  int i = 0;

  assert(string_length > 0);

  while (i <= string_length-1) {
    // SDBM Hash Function
    hash += (hash << 6) + (hash << 16) - hash + string[i];
    i++;
  }
  return hash % table_size;
}


void hashtable_insert (struct HashTable *self, struct HashObject *value) { 
  int hash_index = hash_key(value->key,value->key_length, self->private_size);
  self->H[hash_index] = value;
}

struct HashObject* hashtable_get (struct HashTable *self, char key[], unsigned int key_length) {
  
  assert(key_length > 0);
  int hash_index = hash_key(key,key_length, self->private_size);

  if(self->H[hash_index]) {
    return self->H[hash_index];
  }
  else {
    return NULL;
  }
}

void hashtable_remove (struct HashTable *self, char key[], unsigned int key_length) {
  assert(key_length > 0);

  int hash_index = hash_key(key, key_length, self->private_size);
  self->H[hash_index] = NULL;
}



void hashtable_init(struct HashTable *self, unsigned int hashtable_size) {

  assert (hashtable_size > 0);


  // If hashtable_size is the length of the data you are storing, then pass the size of the data and hashtable will never be loaded more than 2/3
  self->private_size = (3*hashtable_size)/2;

  struct hashtable_operations *hashtable_methods = malloc(sizeof(struct hashtable_operations));
  hashtable_methods->insert = hashtable_insert;
  hashtable_methods->get = hashtable_get;
  hashtable_methods->remove = hashtable_remove;

  self->methods = hashtable_methods;

  self->H = malloc(sizeof(struct HashObject) * self->private_size);
  
  self->entries = 0;
  
  int i = 0;
  while (i < self->private_size) {
    self->H[i] = NULL;
    i++;
  }
}


void hashtable_destroy(struct HashTable *self) {
  free((struct hashtable_operations *) self->methods);
  free(self->H);
}
