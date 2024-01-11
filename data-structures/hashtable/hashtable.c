#include <assert.h>
#include <stdbool.h>
#include "hashtable.h"

void hashtable_copy(HashObject** new_table, HashObject** previous_table, size_t previous_size){
  int i = 0;
  while(i < previous_size){
    new_table[i] = previous_table[i];
    i++;
  }
}

int hash_key(char string[], size_t string_length, size_t table_size) {
  int hash = 0;
  int i = 0;

  assert(string_length > 0);

  while (i <= string_length-1) {
    // SDBM Hash Function
    hash += (hash << 6) + (hash << 16) - hash + string[i];
    i++;
  }
  return hash % table_size;
}


void hashtable_insert (HashTable *self, HashObject *value) {
  if(self->entries+1 <= self->private_size) {
    int hash_index = hash_key(value->key,value->key_length, self->private_size);
    self->H[hash_index] = value;
    self->entries++;
  }
  else {
    size_t previous_size = self->private_size;
    self->private_size = (3*self->private_size)/2;
    HashObject** new_table = malloc(sizeof(HashObject*)* self->private_size);
    hashtable_copy(new_table, self->H, previous_size);
    free(self->H);
    self->H = new_table;
  }
}

 HashObject* hashtable_get (HashTable *self, char key[], size_t key_length) {
  
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



void hashtable_init(HashTable *self, size_t hashtable_size) {

  assert (hashtable_size > 0);


  // If hashtable_size is the length of the data you are storing, then pass the size of the data and hashtable will never be loaded more than 2/3
  self->private_size = (3*hashtable_size)/2;

  hashtable_operations *hashtable_methods = malloc(sizeof(hashtable_operations));
  hashtable_methods->insert = hashtable_insert;
  hashtable_methods->get = hashtable_get;
  hashtable_methods->remove = hashtable_remove;

  self->methods = hashtable_methods;

  self->H = malloc(sizeof(HashObject*) * self->private_size);
  
  self->entries = 0;
  
  int i = 0;
  while (i < self->private_size) {
    self->H[i] = NULL;
    i++;
  }
}


void hashtable_destroy(HashTable *self) {
  free((hashtable_operations *) self->methods);
  free(self->H);
}
