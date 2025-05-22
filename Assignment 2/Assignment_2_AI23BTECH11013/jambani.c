#include "myBST.c"
#include "myHashTable.c"
#include <stdio.h>

int K = 5;

bool wasProducedHere(HashTable *htable, int x);
// void process_file();
void findNeighbors(TreeNode *root, int key, int K);

int main(void) {

  // I wasn't able to check my code with the given csv file . I couldnt pinpoint the error
  // I am attaching a tests.txt file with the test case i used

  char line[256];
  int id;
  char command;
  HashTable *htable = create_table(3107);
  TreeNode *bst_root = NULL;
  bool isRootset = false;
  int line_numb = 0;

  while (fgets(line, sizeof(line), stdin) != NULL) {
    
    line_numb++;

    
    if (line[0] == 'K') {
        clear_table(htable);
      return 0;
      
    }

    sscanf(line, "%d,%c", &id, &command);
    TreeNode *new_node = createnode(id);

    if (command == 'I') {
      //printf("%d\n", line_numb);
      insert_key(htable, id);

      //printf("%d\n", line_numb);
      if (!isRootset) {
        bst_root = new_node;
        isRootset = true;
      } else {
        insert(bst_root, new_node);
      }
      //printf("%d\n", line_numb);
    }

    else if (command == 'D') {
      delete_key(htable, id);
      bst_root = delete_node(bst_root, find_key(bst_root, id));
    }

    else if (command == 'C') {
      if (wasProducedHere(htable, id)) {
        printf("Y\n");
        findNeighbors(bst_root, id, K);
      } else {
        printf("N\n");
      }
    }
  }
}



bool wasProducedHere(HashTable *htable, int x) { return search(htable, x); }



void findNeighbors(TreeNode *root, int key, int K) {
  TreeNode *node = find_key(root, key);
  
  TreeNode *pred = node, *succ = node;
  int pred_count = 0, succ_count = 0;

  while (pred_count < K && (pred = find_predecessor(root, pred)) != NULL) {
    printf("%d ", pred->key);
    // pred->key = find_predecessor(root,pred)->key;
    pred_count++;
  }
  while (succ_count < K && (succ = find_successor(root, succ)) != NULL) {
    printf("%d ", succ->key);
    // succ = find_successor(root,succ);
    succ_count++;
  }
  printf("\n");
}
