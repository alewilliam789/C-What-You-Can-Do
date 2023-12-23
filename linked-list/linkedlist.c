#include "linkedlist.h"
#include <assert.h>
#include <stdlib.h>

struct Node* node_walk(struct Node *head, int index) {
  int i = 0;
  
  struct Node *next_node = head;
  while(i < index) {
    next_node = next_node->next;
    i++;
  }

  return next_node;
}




void linked_list_insert(struct LinkedList *self, int elt) {

  int new_length = self->length+1;
  struct Node *new_node = malloc(sizeof(struct Node));
  new_node->value = elt;


  if(self->length == 0) {
    self->head = new_node;
    self->head->next = NULL;
    self->head->previous = NULL;
    self->length = new_length;
  }
  else if(self->length == 1 && self->private_size >= new_length) {
    self->head->next = new_node;
    self->head->previous = new_node;
    new_node->previous = self->head;
    new_node->next = self->head;
    self->tail = new_node;
    self->length = new_length;
  }
  else if (self->private_size >= new_length) {
    self->tail->next = new_node;
    new_node->previous = self->tail;
    new_node->next = self->head;
    self->tail = new_node;
    self->length = new_length;
  }
}

void linked_list_insert_at(struct LinkedList *self, int index, int elt) {
  int new_length = self->length+1;
  struct Node *new_node = malloc(sizeof(struct Node));
  new_node->value = elt;

  if(self->length == 0) {
    self->head = new_node;
    self->length = new_length;
  }
  else if(self->length == 1 && index == 0) {
    struct Node *old_head = self->head;
    self->head = new_node;
    self->tail = old_head;
    self->tail->previous = self->head;
    self->head->next = self->tail;
  }
  else if(self->length-1 >= index && self->private_size >= new_length) {
    struct Node *index_node = node_walk(self->head,index);
    struct Node *previous_node = index_node->previous;
    previous_node->next = new_node;
    index_node->previous = new_node;
    new_node->previous = previous_node;
    new_node->next = index_node;
    self->length++;
  }
}


int linked_list_remove_at(struct LinkedList *self, int index) {

  if(self->length-1 >= index) {
    struct Node *index_node = node_walk(self->head,index);
    int removed_value = index_node->value;
    struct Node previous_node = *index_node->previous;
    struct Node *next_node = index_node->next;
    previous_node.next = next_node;
    free(index_node);
    self->length--;
    return removed_value;
  }
  else if(self->length-1 == index) {
    struct Node *removed_node = self->tail;
    int removed_value = removed_node->value;
    self->tail = removed_node->previous;
    self->tail->next = self->head;
    free(removed_node);
    self->length--;
    return removed_value;
  }
  else {
    return -1;
  }
}

int linked_list_pop(struct LinkedList *self) {
  if(self->length > 1) {
    int popped_value = self->tail->value;
    struct Node *previous_node = self->tail->previous;
    previous_node->next = self->head;
    free(self->tail);
    self->tail = previous_node;
    self->length--;
    return popped_value;
  }
  else if(self->length == 1) {
    int popped_value = self->head->value;
    free(self->head);
    self->length--;
    return popped_value;
  }
  return -1;
}

int linked_list_get(struct LinkedList *self, int index) {
  if( self->length-1 < index) {
    return -1;
  }

  struct Node *index_node = node_walk(self->head, index);
  return index_node->value;
}

void linked_list_from_array(struct LinkedList *self, int input_array[], int array_length) {
  int new_length = self->length + array_length;

  int i = 0;
  while(i < array_length) {
    self->methods->insert(self,input_array[i]);
    i++;
  }
}

void linked_list_init(struct LinkedList *self, unsigned int size) {

  struct linked_list_operations *linked_list_methods = malloc(sizeof(struct linked_list_operations));

  linked_list_methods->insertAt = &linked_list_insert_at;
  linked_list_methods->removeAt = &linked_list_remove_at;
  linked_list_methods->pop = &linked_list_pop;
  linked_list_methods->insert = &linked_list_insert;
  linked_list_methods->get = &linked_list_get;
  linked_list_methods->fromArray = &linked_list_from_array;


  self->methods = linked_list_methods;



 
  self->head = NULL;
  self->tail = NULL;
  
  assert(size > 0);
    self->private_size = size;

  self->length = 0;
}

void linked_list_destroy(struct LinkedList *self) {
  free((struct linked_list_operations *)self->methods);

  int i;
  for(i = 0; i < self->length-1; i++) {
    self->methods->pop(self);
  };
}
