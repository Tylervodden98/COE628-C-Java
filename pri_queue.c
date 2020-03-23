#include <stdlib.h>
#include <stdio.h>
#include "pri_queue.h"
/** @file pri_queue.c */
static Node_ptr_t head = NULL;
/**
 * Insert a Node into a priority queue.
 * @param priority
 * @param data
 * @author Tyler Vodden
 */
void PQ_insert(int priority, char * data) {
    struct node *que;
    struct node *temp;
    
    
    temp = (struct node*)malloc(sizeof(struct node));
    (*temp).data = data;
    (*temp).priority = priority;
    
    if(head == NULL || priority > (*head).priority)
    {
        (*temp).next = head;
        head = temp;
    }
    else
    {
        que = head;
        while((*que).next != NULL && que -> next -> priority >= priority)
            que = (*que).next;
            temp -> next = que -> next;
            (*que).next = temp;
    }
}
/**
 * Delete and return the node with the highest priority.
 * @return The highest priority Node.
 */
Node_ptr_t PQ_delete() {
    struct node *checkhead = head;
    if(head != NULL)
    { 
        head = (*head).next;   
    }else
    {
        printf("The queue is empty cannot delete.\n");
    }
    return (checkhead);
}
/**
 * Do NOT modify this function.
 * @return A pointer to the head of the list.  (NULL if list is empty.)
 */
Node_ptr_t PQ_get_head() {
    return head;
}

/**
 * Do NOT modify this function.
 * @return the number of items in the queue
 */
int PQ_get_size() {
    int size = 0;
    Node_ptr_t tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next, size++)
        ;
    return size;
}


