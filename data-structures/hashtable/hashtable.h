#ifndef HASHTABLE_H
#define HASHTABLE_H


enum DataType { INT_ARRAY, DOUBLE_ARRAY, STRING, STRUCT, DOUBLE, INT, CHAR };

struct HashObject {
  enum DataType type;
  union {
    char * string;
    int * int_array;
    double * double_array;
    void * struc;
    char character;
    int integer;
    double doubler;
  } value;
  unsigned int key_length;
  char* key;
};

struct HashTable {
  
  void (*init) (struct HashTable* self, unsigned int hashtable_size);
  // Destroys all internally malloced properties.  
  void (*destroy) (struct HashTable* self);
  const struct hashtable_operations* methods;
  int private_size;
  int entries;
  struct HashObject **H;
};

struct hashtable_operations {
  void (*insert) (struct HashTable* self, struct HashObject *value);
  struct HashObject* (*get) (struct HashTable* self, char key[], unsigned int key_length);
  void (*remove) (struct HashTable* self, char key[], unsigned int key_length);
};


void hashtable_init(struct HashTable* self, unsigned int hashtable_size);
void hashtable_destroy(struct HashTable* self);

#endif
