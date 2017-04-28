/**
 * comparator.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is comparator class. It uses functions from others and returns 0 if a->value is less than b->value
 * else it returns 1
 */
#include "comparator.h"

int intComparator(void *a, void *b) {
    int x = getInteger(a);
    int y = getInteger(b);
    if (x == y)
        return 0;
    if (x > y)
        return 1;
    else
        return -1;
}

int realComparator(void *a, void *b) {
    double x = getReal(a);
    double y = getReal(b);
    if (x == y)
        return 0;
    else if (x > y)
        return 1;
    else
        return -1;
}

int stringComparator(void *a, void *b) {
    char *x = getString(a);
    char *y = getString(b);
    return strcmp(x,y);
}