#include <arena.h>
#include <assert.h>
#include <stdint.h>
#include "tree.h"

bool node_peek(TreeNode* node, int32_t key) {
  
  if(node == NULL) {
    return false;
  }
  else if(key > node->key && node->right != NULL) {
    return true;
  }
  else if(key < node->key  && node->left != NULL) {
    return true;
  }
  else {
    return false;
  }
}


void node_swap(Tree* self, TreeNode* parent_node, TreeNode* child_node, TreeNode* swap_node) {

  swap_node->parent = parent_node;

  if(parent_node == NULL) {
    self->root = swap_node;
  }
  else if(parent_node->left == child_node) {
      parent_node->left = swap_node;
  }
  else {
      parent_node->right = swap_node;
  }

  if(child_node->right == swap_node && swap_node != NULL) {
    child_node->right = NULL;
    swap_node->left = child_node->left;
  }
  else if(child_node->left == swap_node && swap_node != NULL) {
    child_node->left = NULL;
    swap_node->right = child_node->right;
  }
  else if(swap_node != NULL){
    swap_node->left = child_node->left;
    swap_node->right = child_node->right;
  }

  if(swap_node->left != NULL) {
    swap_node->left->parent = swap_node;
  }

  if(swap_node->right != NULL) {
    swap_node->right->parent = swap_node;
  }
}


TreeNode* find_predecessor(TreeNode* node) {
  TreeNode* current_node = node->right;
  while(true) {
    if(current_node->left != NULL){
      current_node = current_node->left;
    }
    else {
      break;
    }
  }
  return current_node;
}


TreeNode* tree_walk(TreeNode* node, int32_t key) {
  
  TreeNode* current_node = node;

  while(node_peek(current_node, key)) {
    if(key > current_node->key) {
      current_node = current_node->right;
    }
    else {
      current_node = current_node->left;
    }
  }

  return current_node;
}


bool tree_insert(Tree* self, NodeValue* value, int32_t key) {

  assert(self->entries+1 <= self->private_size);

  TreeNode* new_node = self->arena->alloc(self->arena, sizeof(TreeNode));
  assert(new_node != NULL);

  new_node->key = key;
  new_node->value = *value;
  new_node->left = NULL;
  new_node->right = NULL;

  TreeNode* current_node = self->root;

  TreeNode* parent_node = tree_walk(current_node, new_node->key);
  
  if(parent_node == NULL) {
    new_node->parent = NULL;
    self->root = new_node;
    self->entries++;
    return true;
  }
  else {
    new_node->parent = parent_node;
  }

  if(new_node->key > parent_node->key) {
    parent_node->right = new_node;
  }
  else if(new_node->key < parent_node->key) {
    parent_node->left = new_node;
  }
  
  self->entries++;
  return true;
}


bool tree_remove(Tree* self, int32_t key) {

  if(self->entries == 0) {
    return false;
  }
  
  TreeNode* found_node = tree_walk(self->root,key);

  if(found_node->key != key) {
    return false;
  }

  TreeNode* parent_node = found_node->parent;
  
  
  // Leaf
  if(found_node->left == NULL && found_node->right == NULL) {
    node_swap(self, parent_node, found_node, NULL);
  }
  // Only Left Child
  else if(found_node->right == NULL && found_node->left != NULL) {
    node_swap(self, parent_node,found_node, found_node->left);
  }
  // Only Right Child
  else if(found_node->left == NULL && found_node->right != NULL) {
    node_swap(self, parent_node,found_node, found_node->right);
  }
  // Both & Right Child has no Left Child
  else if(found_node->left != NULL && found_node->right != NULL && found_node->right->left == NULL) {
    node_swap(self,parent_node,found_node,found_node->right);
  }
  // Both & Right Child has Left Subtree
  else {
    TreeNode* predecessor = find_predecessor(found_node);
    if(predecessor->right != NULL) {
      predecessor->parent->left = predecessor->right;
      predecessor->right = NULL;
    }
    else {
      predecessor->parent->left = NULL;
    }
    
    node_swap(self,parent_node,found_node,predecessor);
  }
  
  self->entries--;
  return true;
}


NodeValue* tree_find(Tree* self, int32_t key) {
  
  TreeNode* found_node = tree_walk(self->root, key);
  
  if(found_node->key == key) {
    return &found_node->value;
  }

  return NULL; 
}


static const tree_operations tree_methods = {
  .insert = tree_insert,
  .remove = tree_remove,
  .find = tree_find
};


void tree_init(Tree* self, Arena* arena, size_t private_size) {

  assert(arena != NULL);
  assert(private_size > 0);

  self->arena = arena;

  self->root = NULL;

  self->private_size = private_size;

  self->entries = 0;

  self->methods = &tree_methods;
}


void inorder_tree_free(TreeNode* node) {
  if(node != NULL) {
    TreeNode* left_child = node->left;
    TreeNode* right_child = node->right;

    inorder_tree_free(left_child);
    free(node);
    inorder_tree_free(right_child);
  }
}
