#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"
#include "arena.h"

enum DataType { INT, DOUBLE, STRING, STRUCT };

typedef struct HashObject HashObject;

struct HashObject {
  enum DataType type;
  union {
    char* string;
    char character;
    int* integers;
    int integer;
    double* doubles;
    double doubler;
    void* structure;
  } value;
  char* key;
  size_t key_length;
};



int main() {

  Arena scratch;

  arena_init(&scratch,sizeof(HashTable) + sizeof(void*)*20);

  HashTable a;

  hashtable_init(&a,10,&scratch);

  // Can store a string
  HashObject stringer;
  stringer.type = STRING;
  stringer.value.string = "Hello World";
  stringer.key = "first";
  stringer.key_length = 5;

  a.methods->insert(&a,stringer.key,stringer.key_length,&stringer);
  
  HashObject *stored = a.methods->get(&a, stringer.key, stringer.key_length);
  assert(stored->type == stringer.type);
  assert(stored->value.string[0] == stringer.value.string[0]);
  assert(stored->value.string[1] == stringer.value.string[1]);
  assert(stored->value.string[2] == stringer.value.string[2]);

  // Can store a integer array
  int integers[] = {1,2,3,4,5};
  HashObject intarrer;
  intarrer.type = INT;
  intarrer.value.integers = integers;
  intarrer.key = "second";
  intarrer.key_length = 6;

  a.methods->insert(&a, intarrer.key, intarrer.key_length, &intarrer);

  stored = a.methods->get(&a,intarrer.key,intarrer.key_length);
  assert(stored->type == intarrer.type);
  assert(stored->value.integers[0] == 1);
  assert(stored->value.integers[1] == 2);
  assert(stored->value.integers[2] == 3);
  assert(stored->value.integers[3] == 4);

  
  // Can store a int
  HashObject inter;
  inter.type = INT;
  inter.value.integer= 1;
  inter.key = "third";
  inter.key_length = 5;

  a.methods->insert(&a,inter.key,inter.key_length, &inter);

  stored = a.methods->get(&a,inter.key,inter.key_length);
  assert(stored->type == inter.type);
  assert(stored->value.integer == inter.value.integer);

  // Can store a struct
  struct RandomObject {
    int nothing;
  };
  struct RandomObject randy;
  randy.nothing = 0;

  HashObject structer;
  structer.type = STRUCT;
  structer.value.structure = &randy;
  structer.key = "fourth";
  structer.key_length = 6;

  a.methods->insert(&a,structer.key, structer.key_length, &structer);

  stored = a.methods->get(&a,structer.key,structer.key_length);
  assert(stored->type == STRUCT);
  assert(((struct RandomObject*)stored->value.structure)->nothing == randy.nothing);
  
  // Can remove any DictObject
  a.methods->remove(&a, stringer.key, stringer.key_length);
  assert(a.methods->get(&a,stringer.key,stringer.key_length) == NULL);

  a.methods->remove(&a, intarrer.key, intarrer.key_length);
  assert(a.methods->get(&a,intarrer.key, intarrer.key_length) == NULL);

  a.methods->remove(&a, inter.key, inter.key_length);
  assert(a.methods->get(&a,inter.key,inter.key_length) == NULL);

  a.methods->remove(&a,structer.key,structer.key_length);
  assert(a.methods->get(&a,structer.key, structer.key_length) == NULL);

  arena_destroy(&scratch);

  return 1;
}
