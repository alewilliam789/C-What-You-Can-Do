#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"



int main() {

  HashTable *a = malloc(sizeof(HashTable));

  a->init = hashtable_init;
  a->destroy = hashtable_destroy;

  a->init(a,10);

  // Can store a string
  HashObject stringer;
  stringer.type = STRING;
  stringer.value.string = "Hello World";
  stringer.key = "first";
  stringer.key_length = 5;

  a->methods->insert(a,&stringer);
  
  HashObject *stored = a->methods->get(a, stringer.key, stringer.key_length);
  assert(stored->type == stringer.type);
  assert(stored->value.string[0] == stringer.value.string[0]);
  assert(stored->value.string[1] == stringer.value.string[1]);
  assert(stored->value.string[2] == stringer.value.string[2]);

  // Can store a integer array
  int integers[] = {1,2,3,4,5};
  HashObject intarrer;
  intarrer.type = INT_ARRAY;
  intarrer.value.int_array = integers;
  intarrer.key = "second";
  intarrer.key_length = 6;

  a->methods->insert(a, &intarrer);

  stored = a->methods->get(a,intarrer.key,intarrer.key_length);
  assert(stored->type == intarrer.type);
  assert(stored->value.int_array[0] == 1);
  assert(stored->value.int_array[1] == 2);
  assert(stored->value.int_array[2] == 3);
  assert(stored->value.int_array[3] == 4);

  
  // Can store a int
  HashObject inter;
  inter.type = INT;
  inter.value.integer= 1;
  inter.key = "third";
  inter.key_length = 5;

  a->methods->insert(a,&inter);

  stored = a->methods->get(a,inter.key,inter.key_length);
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
  structer.value.struc = &randy;
  structer.key = "fourth";
  structer.key_length = 6;

  a->methods->insert(a,&structer);

  stored = a->methods->get(a,structer.key,structer.key_length);
  assert(stored->type == STRUCT);
  assert(((struct RandomObject*)stored->value.struc)->nothing == randy.nothing);
  
  // Can remove any DictObject
  a->methods->remove(a, stringer.key, stringer.key_length);
  assert(a->methods->get(a,stringer.key,stringer.key_length) == NULL);

  a->methods->remove(a, intarrer.key, intarrer.key_length);
  assert(a->methods->get(a,intarrer.key, intarrer.key_length) == NULL);

  a->methods->remove(a, inter.key, inter.key_length);
  assert(a->methods->get(a,inter.key,inter.key_length) == NULL);

  a->methods->remove(a,structer.key,structer.key_length);
  assert(a->methods->get(a,structer.key, structer.key_length) == NULL);

  a->destroy(a);

  free(a);

  return 1;
}
