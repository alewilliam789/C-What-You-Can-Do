#include <assert.h>
#include <string.h>
#include "tree.h"
#include "arena.h"

int main(){

  Arena scratch;

  arena_init(&scratch);

  Tree a;

  tree_init(&a,&scratch);

  // Can insert elements
  NodeValue first;
  first.type = INT;
  first.integer = 1;
  first.value_length = 1;
  
  NodeValue third;
  third.type = INT;
  third.integer = 3;
  third.value_length =1;

  NodeValue fourth;
  fourth.type = INT;
  fourth.integer = 4;
  fourth.value_length = 1;

  NodeValue fifth;
  fifth.type = INT;
  fifth.integer = 5;
  fifth.value_length = 1;

  NodeValue seventh;
  seventh.type = INT;
  seventh.integer = 7;
  seventh.value_length = 1;
  
  NodeValue eigth;
  eigth.type = INT;
  eigth.integer = 8;
  eigth.value_length = 1;

  NodeValue nineth;
  nineth.type = INT;
  nineth.integer = 9;
  nineth.value_length = 1;

  bool outcome = a.methods->insert(&a,&fifth,5);
  assert(outcome == true);

  outcome = a.methods->insert(&a,&third,3);
  assert(outcome == true);

  outcome = a.methods->insert(&a,&eigth,8);
  assert(outcome == true);

  outcome = a.methods->insert(&a,&fourth,4);
  assert(outcome == true);

  outcome = a.methods->insert(&a,&seventh,7);
  assert(outcome == true);

  outcome = a.methods->insert(&a,&first,1);
  assert(outcome == true);

  outcome = a.methods->insert(&a,&nineth,9);
  assert(outcome == true);

  // Can retrieve elements
  NodeValue* result = a.methods->find(&a,5);
  assert(result->type == INT);
  assert(result->integer == 5);

  result = a.methods->find(&a,1);
  assert(result->type == INT);
  assert(result->integer == 1);

  result = a.methods->find(&a,4);

  result = a.methods->find(&a,7);
  assert(result->type == INT);
  assert(result->integer == 7);

  result = a.methods->find(&a,9);
  assert(result->type == INT);
  assert(result->integer == 9);

  // Can delete elements
  // Predecessor delete
  outcome = a.methods->remove(&a,5);
  assert(outcome == true);
  assert(a.methods->find(&a,5) == NULL);

  // Right Bubble Delete
  outcome = a.methods->remove(&a,3);
  assert(outcome == true);
  assert(a.methods->find(&a,3) == NULL);

  // Left Bubble Delete
  outcome = a.methods->remove(&a,4);
  assert(outcome == true);
  assert(a.methods->find(&a,4) == NULL);
  
  arena_destroy(&scratch);

  return 1;
}
