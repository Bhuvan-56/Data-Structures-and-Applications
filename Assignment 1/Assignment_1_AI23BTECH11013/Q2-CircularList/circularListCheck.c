#include "circularList.h"

int main()
{
    int i;
    node* u[10];
    node* v[10];
    for (i=0;i<5;i++)
    {
        u[i]=createListNode(2*i);
        v[i]=createListNode(2*i+1);
    }
    for (i=1;i<5;i++)
    {
        insertNode(u[0],u[i]);
        insertNode(v[0],v[i]);
    }
    printList(u[0]);
    printList(v[0]);

    deleteNode(u[2]);
    deleteNode(v[2]);


    printList(mergeList(u[0],v[0]));

    for (i=0;i<5;i++)
    {
        free(u[i]);
        free(v[i]);
    }

    return 0;
}

