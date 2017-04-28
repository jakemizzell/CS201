/**
 * reader.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This file is used by sqsort.c to read a text file or stdin to a queue
 */

#include "reader.h"
#include "scanner.h"
#include "integer.h"
#include "real.h"
#include "string.h"

void intReader(queue *q,FILE *fp) {
    int x = readInt(fp);
    while(!feof(fp)) {
        enqueue(q,newInteger(x));
        x = readInt(fp);
    }
}

void realReader(queue *q,FILE *fp) {
    double x = readReal(fp);
    while(!feof(fp)) {
        enqueue(q,newReal(x));
        x = readReal(fp);
    }
}

void stringReader(queue *q,FILE *fp) {
    char *x = readString(fp);
    while(!feof(fp)) {
        enqueue(q,newString(x));
        x = readString(fp);
    }
}