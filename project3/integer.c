/**
 * integer.c
 *
 * Written originaly by Dr. Lusth but modified by Jake Mizzell for CS201 Spring 2017
 *
 * This is an integer class
 */

#include <stdio.h>
#include <stdlib.h>
#include "integer.h"


integer *newInteger(int x) {
    integer *p = malloc(sizeof(integer));
    if (p == 0) {
        fprintf(stderr,"out of memmory\n");
        exit(-1);
    }
    p->value = x;
    return p;
}

int getInteger(integer *v) {
    return v->value;
}

int setInteger(integer *v,int x) {
    int old = v->value;
    v->value = x;
    return old;
}

void displayInteger(FILE *fp,void *v) {
    fprintf(fp,"%d",getInteger(v));
}

int compareInteger(void *v,void *w) {
    if (!v && !w)
        return 0;
    else if (!v)
        return -1;
    else if (!w)
        return 1;
    else
        return ((integer *) v)->value - ((integer *) w)->value;
}

void freeInteger(integer *v) {
    free(v);
}