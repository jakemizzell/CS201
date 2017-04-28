/**
 * djikstra.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 *
 */

#include <stdio.h>
#include "darray.h"
#include "binomial.h"
#include "vertex.h"
#include "queue.h"


void dijkstra(FILE*,DArray*,Binomial*);
void displayForest(FILE*,queue*);

int main(int argc, char **argv) {
    if (argc < 2)
        fprintf(stderr,"Improper argumnent count!\n");
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
        fprintf(stderr,"Error: %s file didn't open!\n",argv[1]);
    /*Binomial *b = newBinomial(displayVertex,compareVertex,NULL);
    DArray *list = newDArray(displayInteger);
    fillList(fp,list);
    for (int i = 0; i < sizeDArray(list); i++) {
        Vertex *temp = getDArray(list,i);
        insertBinomial(b,temp);
    }
    displayBinomial(stdout,b);*/


    DArray *list = newDArray(displayInteger);
    fillList(fp,list);
    Binomial *b = newBinomial(displayVertex,compareVertex,updateVertex);
    for (int i = 0; i < sizeDArray(list); i++) {
        Vertex *temp = getDArray(list,i);
        temp->node = insertBinomial(b,temp);
    }
    dijkstra(stdout,list,b);

    //TESTING binomial
    /*Binomial *heap = newBinomial(displayInteger,compareInteger,NULL);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(4));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(8));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(16));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(5));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Inserting...\n");
    (void) insertBinomial(heap,newInteger(1));
    displayBinomial(stdout,heap);
    fprintf(stdout,"Extracting...\n");
    (void) extractBinomial(heap);
    displayBinomial(stdout,heap);
    fprintf(stdout,"Extracting...\n");
    (void) extractBinomial(heap);
    displayBinomial(stdout,heap);
    fprintf(stdout,"Extracting...\n");
    (void) extractBinomial(heap);
    displayBinomial(stdout,heap);*/

    //TESTING vertex.c
    /*DArray *list = newDArray(displayInteger);
    fillList(fp,list);
    printf("List is now:\n");
    printList(stdout,list);*/


    //TESTING DArray
    /*DArray *array = newDArray(displayInteger);
    insertDArray(array,newInteger(3));
    removeDArray(array);
    displayDArray(stdout,array);
    insertDArray(array,newInteger(4));
    insertDArray(array,newInteger(7));
    insertDArray(array,newInteger(2));
    displayDArray(stdout,array);
    for (int i = 0; i < 5000; i++) insertDArray(array,newInteger(7));
    for (int i = 0; i < 4999; i++) removeDArray(array);
    displayDArray(stdout,array);
    fprintf(stdout,"%d\n",getInteger(getDArray(array,0)));*/

   if(fp != NULL)
       fclose(fp);
   return 0;
}

void displayForest(FILE *fp, queue *a) {
    if (sizeQueue(a) == 0)
        return;
    Binomial *b = newBinomial(displayVertex,compareVertex,updateVertex);
    int s = sizeQueue(a);
    int maxSteps = 0;
    //find the largest step number and insert everything into a heap
    for(int i = 0; i < s; i++) {
        Vertex *v = (Vertex*)dequeue(a);
        if (v->steps > maxSteps)
            maxSteps = v->steps;
        insertBinomial(b,v);
    }
    //set up a queue array
    queue *level[maxSteps];
    for(int j=0; j <= maxSteps; j++){
        level[j] = newQueue(displayVertex);
    }
    //insert things into the queue
    for(int k=0; k < s; k++){
        Vertex *v = (Vertex *)extractBinomial(b);
        enqueue(level[v->steps], v);
    }
    //print the queues
    for(int a=0; a <= maxSteps; a++){
        printf("%d : ", a);
        while(sizeQueue(level[a]) != 0){
            Vertex *print = (Vertex *) dequeue(level[a]);
            displayVertex(fp, print);
            if(sizeQueue(level[a]) > 0)
                fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "----\n");
}


void dijkstra(FILE *fp, DArray *list, Binomial *b) {
    if(sizeDArray(list) == 0) {
        fprintf(fp,"0:\n----\n");
        return;
    }
    queue *visited = newQueue(displayVertex);
    Vertex *min = getMinVertex(list);
    min->distance = 0;
    min->prev = min;
    min->steps = 0;
    while(sizeBinomial(b) != 0) {
        Vertex *u = (Vertex*)extractBinomial(b);
        if(u->prev == NULL) {
            u->distance = 0;
            displayForest(fp,visited);
            visited = newQueue(displayVertex);
        }
        enqueue(visited,u);
        u->visited = 1;
        for(int i = 0; i < sizeDArray(u->neighbors); i++) {
            Neighbor *n = (Neighbor*)getDArray(u->neighbors,i);
            //get the Neighbor in vertex list
            Vertex *v = getNeighborVertex(list,n);
            if(v->visited != 1) {
                if (u->distance + n->weight < v->distance) {
                    v->prev = u;
                    v->distance = u->distance + n->weight;
                    v->steps = v->prev->steps + 1;
                    decreaseKeyBinomial(b,v->node,v);
                }
            }
        }
    }
    displayForest(fp,visited);
}