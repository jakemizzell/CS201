/**
 * queue.h
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is the header file for queue.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "sll.h"

#ifndef __QUEUE_INCLUDED__
#define __QUEUE_INCLUDED__

typedef struct queue
{
    sll *list;
} queue;

extern queue *newQueue(void (*d)(FILE *,void *));   //constructor
extern void enqueue(queue *items,void *value);      //stores a generic value
extern void *dequeue(queue *items);                 //returns a generic value
extern void *peekQueue(queue *items);               //returns a generic value
extern int sizeQueue(queue *items);
extern void displayQueue(FILE *fp,queue *items);

#endif