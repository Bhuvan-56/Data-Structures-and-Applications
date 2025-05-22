/* Header file for BST */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {

  int key; // Key stored in the node

  /* pointers to left, right child and parent*/
  struct TreeNode *left;
  struct TreeNode *right;
  struct TreeNode *parent;

  /* Add any other data as appropriate here */

} TreeNode;

/* Insert node into the subtree rooted at root */

void insert(TreeNode *root, TreeNode *node);

/* Delete the node pointed to by node, return a pointer to the (possibly new)
 * root node of the tree */
TreeNode *delete_node(TreeNode *root, TreeNode *node);

/* Return a pointer to the successor of a given node in the tree */

TreeNode *find_successor(TreeNode *root, TreeNode *node);

/* Return a pointer to the predecessor of a given node in the tree */
TreeNode *find_predecessor(TreeNode *root, TreeNode *node);

/* Return a pointer to the Node containing key in the subtree rooted at *root */
TreeNode *find_key(TreeNode *root, int key);