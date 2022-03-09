/*
* Sorting array of linked lists. Using min-heap. Merging sorted arrays.
*
*/


#include <stdlib.h>
#include <stdio.h>


#include "merge_k.h"  // includes list.h


void insert_sort(struct node** head_ref, struct node* new_node);

/*  Sorts linked list L in pace using insertion sort.
 Assumes L has a dummy node.
 */
void sort_list(nodePT L)
{
    struct node *sortedNode = NULL;
    
    // Traverse the given linked list and insert every
    // node to sorted
    struct node *current = L;

    while (current != NULL)
    {
        struct node *next = current->next;
        insert_sort(&sortedNode, current);
        current = next;
    }

    L = sortedNode;


}



void insert_sort(struct node** L, struct node* new_node)
{
    struct node* currentNode;

    /* check for the head of linked list */
    if (*L == NULL || (*L)->data >= new_node->data)
    {
        new_node->next = *L;
        *L = new_node;
    }

    else
    {
        currentNode = *L;

        while (currentNode->next!=NULL && currentNode->next->data < new_node->data)
        {
            currentNode = currentNode->next;
        }

        new_node->next = currentNode->next;
        currentNode->next = new_node;
    }

}



void sinkDown(int N,int p,nodePT A[])
{
    int left = 2*p+1;// index of left child of p
    int right = (2*p)+2; // index of right child of p

    int index= p;

    nodePT temp = NULL;


    if ((left< N)&&((A[left])->data < (A[index])->data))
    {
        index = left;
    }


    if ((right<N)&&((A[right])->data < (A[index])->data))
    {
        index = right;
    }


    if (index!=p)
    {
                
        temp = A[index];
        A[index] = A[p];
        A[p] = temp;
        
       // swap A[p] <-> A[index]
        sinkDown(N,index,A);
    
    }
    
}


void make_heap(int k, nodePT heap[k])
{
    
    nodePT dumNode = NULL;

    int p = 0;
    int i = 0;


    for(i = 0; i < k ;i++)
    {
       dumNode = heap[i];
       heap[i] = heap[i]->next;
       free(dumNode);
        
    }


    for (p = (k/2)-1; p>=0; p--)
    {
        sinkDown(k,p,heap);
    }


}


nodePT remove_min(int* k, nodePT heap[(*k)])
{
	// Replace the place holder code with the correct code
    struct node* minVal = NULL;
    minVal = heap[0];
    
    heap[0] = heap[0]->next;

    if(heap[0] == NULL)
    {
       
        (*k) = (*k)-1;
         heap[0] = heap[(*k)];
        
    }
    
    
    sinkDown(*k,0,heap);
    return minVal;  
}




nodePT merge_k(int k, nodePT heap[k])
{
    nodePT result_list = new_list();
    nodePT tempNode = result_list;


    while(k!=0)
    {
        result_list->next = remove_min(&k,heap);
        result_list= result_list->next;
        
    }


    return tempNode;
    
}


