/**
 * stack.h
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This class is the header file for stack.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

#ifndef __STACK_INCLUDED__
#define __STACK_INCLUDED__

typedef struct stack
{
    dll *list;
} stack;

extern stack *newStack(void (*d)(FILE *,void *));   //constructor
extern void push(stack *items,void *value);         //stores a generic value
extern void *pop(stack *items);                     //returns a generic value
extern void *peekStack(stack *items);               //returns a generic value
extern int sizeStack(stack *items);
extern void displayStack(FILE *,stack *items);

#endif