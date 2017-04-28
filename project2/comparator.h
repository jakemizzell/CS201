/**
 * comparator.h
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is the header file for comparator.c
 */


#include <string.h>
#include "integer.h"
#include "real.h"
#include "string.h"

#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*,void*);

extern int intComparator(void *a, void *b);
extern int realComparator(void *a, void *b);
extern int stringComparator(void *a, void *b);

#endif