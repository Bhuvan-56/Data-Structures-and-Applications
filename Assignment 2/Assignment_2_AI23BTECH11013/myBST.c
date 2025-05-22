#include "myBST.h"
#include <stdlib.h>

struct TreeNode *createnode(int key);
struct TreeNode *minimum_BST(TreeNode *root);
struct TreeNode *maximum_BST(TreeNode *root);



struct TreeNode *createnode(int key) {
  struct TreeNode *new_node =
      malloc(sizeof(TreeNode));

  new_node->key = key;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->parent = NULL;

  // printf("%d is created \n",new_node->key);

  return new_node;
}

void insert(struct TreeNode *root, struct TreeNode *node) {
  if (node == NULL|| root == NULL) {
    // printf("Not possible\n");
    return;
  }

  

  struct TreeNode *temp = root;
  struct TreeNode *temp_1 = NULL;

  while (temp != NULL) {
    temp_1 = temp;
    if (node->key > temp->key) {
      temp = temp->right;
    } else {
      temp = temp->left;
    }
  }

  if (node->key > temp_1->key) {
    temp_1->right = node;
  } else {
    temp_1->left = node;
  }

  node->parent = temp_1;

  // printf("%d is inserted at its parent %d\n",node->key,temp_1->key);
}

struct TreeNode *find_key(TreeNode *root, int key) {
  struct TreeNode *temp = root;
  while (temp != NULL) {
    if (key == temp->key) {
      // printf("Element found at its parent %d\n",temp->parent->key);
      return temp;
    }

    else if (key > temp->key) {
      temp = temp->right;
    } else if (key < temp->key) {
      temp = temp->left;
    }

    else {
      // printf("Element not found\n");
      return NULL;
    }
  }
}



void transplant(TreeNode **root, TreeNode *u, TreeNode *v) {
  if (u->parent == NULL) {
    *root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  }

  else {
    u->parent->right = v;
  }

  if (v != NULL) {
    v->parent = u->parent;
  }
}

TreeNode *delete_node(TreeNode *root, TreeNode *node) {
  if(root == NULL || node == NULL){
    return root;
  }
  if (node->left == NULL) {
    transplant(&root, node, node->right);
  } else if (node->right == NULL) {
    transplant(&root, node, node->left);
  } else {
    TreeNode *y = minimum_BST(node->right);
    if (y->parent != node) {
      transplant(&root, y, y->right);
      y->right = node->right;
      y->right->parent = y;
    }

    transplant(&root, node, y);
    y->left = node->left;
    y->left->parent = y;
  }
  free(node);
  return root;
}

TreeNode *find_successor(TreeNode *root, TreeNode *node) {
  if (node->right != NULL) {
    // The successor is the minimum of the right subtree
    return minimum_BST(node->right);
  }

  TreeNode *successor = NULL;
  TreeNode *current = root;

  while (current != NULL) {
    if (node->key < current->key) {
      successor = current; // This could be a successor
      current = current->left;
    } else if (node->key > current->key) {
      current = current->right;
    } else {
      break; // The node itself
    }
  }
  return successor;
}

TreeNode *find_predecessor(TreeNode *root, TreeNode *node) {
  if (node->left != NULL) {
    // The predecessor is the maximum of the left subtree
    return maximum_BST(node->left);
  }

  TreeNode *predecessor = NULL;
  TreeNode *current = root;

  while (current != NULL) {
    if (node->key < current->key) {
      current = current->left;
    } else if (node->key > current->key) {
      predecessor = current; // This could be a predecessor
      current = current->right;
    } else {
      break; // The node itself
    }
  }
  return predecessor;
}

struct TreeNode *minimum_BST(TreeNode *root) {
  if (root->left == NULL) {
    // printf("Hello\n");
    return root;
  }
  struct TreeNode *present = root;
  while (present != NULL && present->left != NULL) {
    present = present->left;
  }

  // printf("The minimum of the sub tree rooted at %d is
  // %d\n",root->key,present->key);
  return present;
}

struct TreeNode *maximum_BST(TreeNode *root) {
  if (root->right == NULL) {
    return root;
  }
  struct TreeNode *present = root;
  while (present != NULL && present->right != NULL) {
    present = present->right;
  }

  // printf("The maximum of the sub tree rooted at %d is
  // %d\n",root->key,present->key);
  return present;
}
