/**
 * queue.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is a queue class that can enqueue from the rear and dequeue
 * from the front. You can peek at the first value. You can also get
 * the size of the queue and display it
 */

#include "queue.h"

queue *newQueue(void (*d)(FILE *,void *)) {
    queue *items = malloc(sizeof(queue));
    if (items == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->list = newSLL(d);
    return items;
}

void enqueue(queue *items,void *value) {
    //if there the queue is empty insert at head
    if (items->list == NULL)
        insertSLL(items->list,0,value);
    //else insert at tail
    else
        insertSLL(items->list,items->list->size,value);
}

void *dequeue(queue *items) {
    //remove from head
    return removeSLL(items->list,0);
}

void *peekQueue(queue *items) {
    return getSLL(items->list,0);
}

int sizeQueue(queue *items) {
    return sizeSLL(items->list);
}

void displayQueue(FILE *fp,queue *items) {
    displaySLL(fp,items->list);
}