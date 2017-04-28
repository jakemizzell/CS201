/**
 * test-s.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This file test the stack.c & stack.h files
 */

#include <stdio.h>
#include "stack.h"
#include "integer.h"

static void showStack(stack *s)
{
    printf("The stack is ");
    displayStack(stdout,s);
    printf(".\n");
}

int main(void)
{
    stack *items = newStack(displayInteger);
    showStack(items);
    push(items,newInteger(3));
    showStack(items);
    printf("The value ");
    displayInteger(stdout,pop(items));
    printf(" was popped.\n");
    showStack(items);
    push(items,newInteger(2));
    showStack(items);
    return 0;
}