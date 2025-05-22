
/* Header file for hash table; do not modify */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct HashTable{
	
	//Based on your implementation of the HashTable, you may fill in this struct accordingly
	// e.g. you may want to store an array of pointers to linked lists if using Chaining, or just an array of ints if using OpenAddressing	

	 struct Node{
		int key;
		int value;
		struct Node *next;
	};
	
	struct arrayitem{
		struct Node *head;
		struct Node *tail;
	};

	struct arrayitem *htable; // The array of linked lists we use for chaining

	
	
	int size;  // current "size" of the table
	int count; //current number of elements in the hash table
} HashTable;




/* Do not modify below this line */

/* creates a hash table that can hold max_capacity elements */
HashTable* create_table(int max_capacity);
	
	
/* Insert a key into the Hashtable. Return TRUE if element not already present, else FALSE */
bool insert_key(HashTable *htable, int key);  


/* Deletes a key from the HashTable, given a pointer to it */
bool delete_key(HashTable *htable, int key);

/* Returns a boolean value if the table contains the key, if it exists, 0 otherwise */
bool search(HashTable *htable, int key);


/* Clear the Hash Table and release any memory allocated to it*/
void clear_table(HashTable *htable);