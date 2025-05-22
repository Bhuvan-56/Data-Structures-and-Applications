#include "myHashTable.h"

int hashfunctt(HashTable* htable,int key);
int findtheindex(struct Node *list,int key);
struct Node* getele(struct Node *list,int find_index);
void display_table();

int max_capacity;




HashTable* create_table(int max_capacity)
{
	HashTable* table = malloc(sizeof(HashTable));
	table->htable = malloc(max_capacity * sizeof(struct arrayitem));
	table->size = max_capacity;
	table->count =0;

	for(int i=0;i<max_capacity;i++){

		table->htable[i].head = NULL;
		table->htable[i].tail = NULL;
	}
	//printf("Table Created\n");
	return table;
}

bool insert_key(HashTable *htable, int key)
{
	int index = hashfunctt(htable, key); // We get the position to go from the hash function

	struct Node *list = htable->htable[index].head; // for the index we got we look at the linked list which is present there

	struct Node *item = (struct Node*) malloc(sizeof(struct Node)); 

	item->key = key;
	//item->value = value;
	item->next = NULL; // The key is created with its attributes


	if(list == NULL){
		htable->htable[index].head = item; // if theres no linked list present this key would be the first key there
		htable->htable[index].tail = item;
		htable->count++;
		//printf("Added %d into an empty linked list\n",key);
		return true;
	}
	else {
		int find_index = findtheindex(list,key); // checks if the key we want to insert is already in the linked list
		if(find_index == -1){
			htable->htable[index].tail->next = item; // if not inserted at the end
			htable->htable[index].tail = item;
			htable->count++;
			//printf("Added %d into an existing linked list\n",key);

			return true;
		}
			//printf("%d is already in the linked list\n",key);
		
	}

}




// void display_table(HashTable *table){
	
// 	for(int i=0;i<max;i++){
// 		struct Node *temp = table->htable[i].head; // points to the linked lists one by one 
// 		if(temp == NULL){
// 			//printf("This %d line is empty\n",i);
// 		}
// 		else{
// 			//printf("This %d line is non-empty\n",i);
// 			while(temp!=NULL){
// 				//printf("It has key= %d,value = %d\n",temp->key,temp->value); // it goes linearly and displays the elements present
// 				temp = temp->next; // once a element is displayed ,its successor is next
// 			}
// 			//printf("\n");
// 		}
// 	}
// }

bool delete_key(HashTable *htable, int key){
		int index = hashfunctt(htable,key);
		struct Node *list = htable->htable[index].head; // Linked list corresponding to the index of the key
		if(list == NULL){
			//printf("Elem dne\n");
		}

		else{
			int find_index = findtheindex(list,key); // gets the index of key in certain linked list
			if(find_index==-1){
				//printf("Elem dne\n");
			}

			else{
				struct Node *temp = list;
				if(temp->key == key){
					htable->htable[index].head = temp->next; // if its the head then new head would be its next elemnt
					//printf("Key %d removed\n",key);
					return true;
				}

				while(temp->next->key != key){
					temp = temp->next;				// if not it finds the predecessor of the key 
				}

				if(htable->htable[index].tail == temp->next){ // if our key is the tail of the linked list
					temp->next = NULL;
					htable->htable[index].tail = NULL; // it is removed
					//printf("Key %d removed\n",key);
					return true;
				}

				else{
					temp->next = temp->next->next; // if not its deleted the linked list way
					//printf("Key %d removed\n",key);
					return true;
				}
			}
		}
}

bool search(HashTable *htable, int key){
	int index = hashfunctt(htable,key);
	struct Node *list = htable->htable[index].head; // Using the key given we find the linked list in which the key can be in

	int search_index = findtheindex(list,key);
	if(search_index != -1){
		//printf("Its there\n"); // using the findtheindex function we search for the key in this linked list
		return true;
	}

	else{
		//printf("It isnt there\n");
		return false;
	}
}

void clear_table(HashTable *htable){
	for(int i=0;i<htable->size;i++){
		struct Node *current = htable->htable[i].head; // gets the pointer to the lisned kist in that index

		while(current != NULL){
			struct Node *temp = current;
			current = current->next; // deleting each elemnt by element in the linked list
			free(temp);
		}

		htable->htable[i].head = NULL; // once all elements are deleetd linked list is then deleted by pointing to NULL
		htable->htable[i].tail = NULL;
	}

		free(htable->htable);
		free(htable);

		//printf("Hash table vanished\n");
}

int hashfunctt(HashTable* htable ,int key){
    return key % htable->size;// The hash function we are using
}

int findtheindex(struct Node *list,int key)
{
    int ret=0;
    struct Node *temp = list;

    while(temp!=NULL){
        if(temp->key == key){
            return ret; // returns the index of the found key
        }
        temp = temp->next; // if not goes to the next ele
        ret++; // index incremented

    }
    return -1;
}

struct Node* getele(struct Node *list,int find_index){

    int i=0;

    struct Node *temp = list; // Intialised to the list 

    while(i!=find_index){
        temp = temp->next; // Using the index as the means of searching the element
        i++;
    }
    return temp; // element returned once found
}

