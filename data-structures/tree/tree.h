#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct NodeValue NodeValue;

enum DataType { INT, DOUBLE, STRING, STRUCT };

struct NodeValue {
  enum DataType type;
  union {
    char* string;
    char character;
    int* integers;
    int integer;
    double* doubles;
    double doubler;
    void* structure;
  };
  size_t value_length;
};


typedef struct TreeNode TreeNode;

struct TreeNode {
  int32_t key;
  NodeValue value;
  TreeNode* parent;
  TreeNode* left;
  TreeNode* right;
  enum {NONE, BLACK, RED} color;
};


typedef struct Tree Tree;
typedef struct tree_operations tree_operations;

struct Tree {
  void (*init) (Tree* self, size_t tree_size);
  void (*destroy) (Tree* self);
  TreeNode* root;
  TreeNode* nil;
  const tree_operations* methods;
  size_t private_size;
  size_t entries;
};

struct tree_operations {
  bool (*insert) (Tree* self, NodeValue* elt, int32_t key);
  bool (*remove) (Tree* self, int32_t key);
  NodeValue* (*find) (Tree* self, int32_t key);
};


void tree_init(Tree* self, size_t tree_size);
void tree_destroy(Tree* self);

#endif
