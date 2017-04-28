/**
 * sqsort.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is the main program. It is a program to read in integers, reals,
 * or strings from a file or stdin. It then can sort them largest to smallest
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comparator.h"
#include "reader.h"
#include "stack.h"
#include "integer.h"
#include "real.h"
#include "string.h"

typedef void (*Printer)(FILE*,void*);

int sort(Comparator,queue*,queue*,stack*,int,int);


int main(int argc, char **argv) {
    Comparator comp;
    Printer print;
    Reader read;
    FILE *fp;
    if (argc == 2)
        fp = stdin;
    else if (argc == 3) {
        fp = fopen(argv[2], "r");
        //errror checking
        if (fp == NULL) {
            fprintf(stderr,"Error: file didn't open!");
            exit(1);
        }
    }
    else {
        fprintf(stdout, "unknown flag '%c', valid flags are -d, -r, -s, and -v",argv[1][1]);
        exit(1);
    }
    if (strcmp(argv[1],"-v") == 0) {
        fprintf(stdout,"Jacob B. Mizzell\n");
        exit(0);
    }
    else if (strcmp(argv[1],"-d") == 0) {
        comp = intComparator;
        print = displayInteger;
        read = intReader;
    }
    else if (strcmp(argv[1],"-r") == 0) {
        comp = realComparator;
        print = displayReal;
        read = realReader;
    }
    else if (strcmp(argv[1],"-s") == 0) {
        comp = stringComparator;
        print = displayString;
        read = stringReader;
    }
    else {
        fprintf(stdout, "unknown flag '%c', valid flags are -d, -r, -s, and -v",argv[1][1]);
        exit(1);
    }
    queue *input = newQueue(print);
    queue *output = newQueue(print);
    stack *stack1 = newStack(print);
    read(input,fp);
    fclose(fp);
    displayQueue(stdout,input);
    int passCount = sort(comp,input,output,stack1,0,1);
    //if it was only one pass
    if (passCount == 1) {
        printf("\n");
        displayQueue(stdout,input);
    }
    printf("\n");
    return 0;
}

int sort (Comparator comp,queue *input, queue *output, stack *stack1, int stackUsed, int passes) {
    void *qV;//, *qPV, *sV;
    while (sizeQueue(input) != 0) {
        //peekStack is greater than or equal to peekQueue && stack && queue aren't empty move from stack
        if ((sizeStack(stack1) != 0) && (sizeQueue(input) != 0) && (comp(peekStack(stack1),peekQueue(input)) >= 0))
            enqueue(output,pop(stack1));
        else {
            qV = dequeue(input);
            //if dequeue is less than peekQueue push to stack
            if ((sizeQueue(input) != 0) && (comp(qV,peekQueue(input)) < 0)) {
                push(stack1,qV);
                stackUsed = 1;
            }
            //if dequeue is greater equal than peekQueue
            else
                enqueue(output,qV);
        }
        /*//error checking
        printf("\nInput: \n");
        displayQueue(stdout,input);
        printf("\nStack: \n");
        displayStack(stdout,stack1);
        printf("\nOutput: \n");
        displayQueue(stdout,output);
        printf("\n");*/
    }
    //if there is anything in the stack send it to the queue
    while (sizeStack(stack1) != 0)
        enqueue(output, pop(stack1));
    unionSLL(input->list,output->list);
    //keep running it until you don't put anything in the stack
    if (stackUsed != 0) {
        printf("\n");
        displayQueue(stdout, input);
        passes += sort(comp,input,output,stack1,0,passes);
    }
    return passes;
}
