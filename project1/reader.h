/**
 * reader.h
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is the header file for reader.c
 */

#ifndef __READER_H__
#define __READER_H__

#include "queue.h"

typedef void (*Reader)(queue*,FILE*);

extern void intReader(queue*,FILE*);
extern void realReader(queue*,FILE *);
extern void stringReader(queue*,FILE*);


#endif