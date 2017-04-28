/**
 * test-q.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is a testing file for queue.c & queue.h
 */

#include <stdio.h>
#include "queue.h"
#include "integer.h"
#include <time.h>

static void showQueue(queue *s)
{
    printf("The queue is ");
    displayQueue(stdout,s);
    printf(".\n");
}

int main(void)
{
    clock_t begin = clock();
    queue *a = newQueue(displayInteger);
    int i;
    for (i = 0; i < 30000; i++) {
        enqueue(a,newInteger(i));
    }
    for (i = 0; i < 30000; i++) {
        dequeue(a);
    }
    displayQueue(stdout,a);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nSeconds: %f\n", time_spent);
    queue *items = newQueue(displayInteger);
    showQueue(items);
    /*queue *items = newQueue(displayInteger);
    showQueue(items);
    printf("Size: %d\n",sizeQueue(items));
    enqueue(items,newInteger(7));
    showQueue(items);
    printf("Size: %d\n",sizeQueue(items));
    dequeue(items);
    showQueue(items);
    printf("Size: %d\n",sizeQueue(items));
    enqueue(items,newInteger(2));
    showQueue(items);
    printf("Size: %d\n",sizeQueue(items));
    enqueue(items,newInteger(5));
    enqueue(items,newInteger(7));
    enqueue(items,newInteger(13));
    showQueue(items);
    printf("The value ");
    displayInteger(stdout,dequeue(items));
    printf(" was popped.\n");
    showQueue(items);
    enqueue(items,newInteger(2));
    showQueue(items);
    int x = getInteger((integer *) peekQueue(items));
    printf("The first item is %d.\n",x);*/
    return 0;
}