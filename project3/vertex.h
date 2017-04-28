//
// Created by jakem on 3/28/2017.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "darray.h"
#include "binomial.h"
#include "integer.h"
#include "scanner.h"

#ifndef __VERTEX_INCLUDED__
#define __VERTEX_INCLUDED__

typedef struct Vertex {
    int value;
    struct Vertex *prev;
    int distance;
    int steps;
    int visited;
    DArray *neighbors;
    BinomialNode *node;
}Vertex;

typedef struct Neighbor {
    Vertex *v;
    int weight;
}Neighbor;

typedef struct edge {
    int vertex1;
    int vertex2;
    int weight;
}edge;

extern Vertex *newVertex(int);
extern Neighbor *newNeighbor(int,int);
extern void insertVertex(int,int,int,DArray*);
extern Vertex *getVertex(int,DArray*);
extern Neighbor *getNeighbor(int,DArray*);
extern Vertex *getMinVertex(DArray*);
extern Vertex *getNeighborVertex(DArray*,Neighbor*);
extern int getWeight(Vertex*);
extern void fillList(FILE*,DArray*);
extern void printList(FILE*,DArray*);
extern void displayVertex(FILE*,void*);
extern void displayWeight(FILE*,Vertex*);
extern int compareVertex(void*,void*);
extern void updateVertex(void*,BinomialNode*);

extern edge *readFile(FILE*);

#endif
