#include <assert.h>
#include "hash.h"



int SDBM(char key[], size_t key_length) {
  int hash = 0;
  size_t i = 0;

  assert(key_length > 0);

  while (i <= key_length-1) {
    // SDBM Hash Function
    hash += (hash << 6) + (hash << 16) - hash + key[i];
    i++;
  }
  return hash;
}
