#ifndef LINKED_LIST_H
#define LINKED_LIST_H


struct Node {
  int value;
  struct Node *next;
  struct Node *previous;
};


struct LinkedList {
  
  void (*init) (struct LinkedList *self, unsigned int linked_list_size);  
  void (*destroy) (struct LinkedList *self);
  const struct linked_list_operations *methods;
  int length;
  int private_size;
  struct Node *head;
  struct Node *tail;
};

struct linked_list_operations {
  void (*insert) (struct LinkedList *self,int elt);
  void (*insertAt) (struct LinkedList *self, int elt, int index);
  int (*pop) (struct LinkedList *self);
  int (*removeAt) (struct LinkedList *self, int index);
  int (*get) (struct LinkedList *self, int index);
  void (*fromArray) (struct LinkedList *self, int input_array[],int length);
};


void linked_list_init(struct LinkedList *self, unsigned int linked_list_size);
void linked_list_destroy(struct LinkedList *self);

#endif
