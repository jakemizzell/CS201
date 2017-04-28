/**
 * stack.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This file can create a new stack, push, and pop from a stack.
 * It can also get a value and the size as well as display the stack
 */

#include "stack.h"

stack *newStack(void (*d)(FILE *,void *)) {
    stack *items = malloc(sizeof(stack));
    if (items == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->list = newDLL(d);
    return items;
}

void push(stack *items,void *value) {
    insertDLL(items->list,0,value);
}

void *pop(stack *items) {
    return removeDLL(items->list,0);
}

void *peekStack(stack *items) {
    return getDLL(items->list,0);
}

int sizeStack(stack *items) {
    return sizeDLL(items->list);
}

void displayStack(FILE *fp,stack *items) {
    displayDLL(fp,items->list);
}