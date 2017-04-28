/**
 * binomial.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * Binomial class, this creates a Binomial Heap, manipulates, it and displays it
 */

#include "binomial.h"
#include <stdlib.h>
#include "queue.h"


static BinomialNode *bubbleUp(Binomial*,BinomialNode*);
static BinomialNode *combine(Binomial*,BinomialNode*,BinomialNode*);
static void consolidate(Binomial*,BinomialNode*);
static void displayLevelOrder(FILE*,BinomialNode *);
static void findExtreme(Binomial*);
static int getDegree(BinomialNode *);
static void *getSubHeap(DArray*,int);
static void merge(Binomial*,DArray*);
static void updateExtreme(Binomial*,BinomialNode*);

typedef struct BinomialNode {
    void *value;
    DArray *children;
    struct BinomialNode *parent;
    void (*display)(FILE *,void *);
}BinomialNode;

/**
 * create a new BinomialNode
 * @param d is the display function pointer
 * @param v is the value that you're adding
 * @return the new BinomialNode
 */
BinomialNode *newBinomialNode(void (*d)(FILE *,void *), void *v) {
    BinomialNode *n = malloc(sizeof(BinomialNode));
    if (n == 0) {
            fprintf(stderr, "out of memory");
            exit(-1);
        }
    n->value = v;
    n->children = newDArray(d);
    n->parent = n;
    n->display = d;
    return n;
}

/**
 * display the node's value;
 * @param fp where you're printing to
 * @param v is box you're sending to print
 */
void displayBinomialNode(FILE *fp, BinomialNode *n) {
    if (n == NULL) {
        fprintf(stderr,"displayNode Empty\n");
    }
    else {
        n->display(fp, n->value);
        fprintf(fp, "-%d", getDegree(n));
        if (n->parent != n) {
            fprintf(fp, "(");
            n->parent->display(fp, n->parent->value);
            fprintf(fp, "-%d)", getDegree(n->parent));
        }
    }
}

typedef struct Binomial {
    DArray *rootlist;
    int (*compare)(void *,void *);
    void (*update)(void *,BinomialNode *);
    BinomialNode *extreme;
    int size;
    void (*display)(FILE *,void *);
}Binomial;

/**
 * Create a new Binomial
 * @param d is the diplay function pointer
 * @param c is the comparator function pointer
 * @param u is the updater funciton pointer
 * @return the new Binomial
 */
Binomial *newBinomial(void (*d)(FILE *,void *), int (*c)(void *,void *), void (*u)(void *,BinomialNode *)) {
    Binomial *b = malloc(sizeof(Binomial));
    b->rootlist = newDArray(d);
    b->compare = c;
    b->update = u;
    b->extreme = 0;
    b->size = 0;
    b->display = d;
    return b;
}

/**
 * insert a value into the Binomial
 * @param b is the Binomial
 * @param v is the value to be inserted
 * @return the new Binomial
 */
BinomialNode *insertBinomial(Binomial *b, void *v) {
    BinomialNode *n = newBinomialNode(b->display,v);
    updateExtreme(b,n);
    consolidate(b,n);
    b->size++;
    /*printf("The value inserted ");
    displayBinomialNode(stdout,n);
    printf("\n");
    printf("Tree is now\n");
    displayBinomial(stdout,b);
    printf("The new extreme: ");
    displayBinomialNode(stdout,b->extreme);
    printf("\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");*/
    return n;
}

/**
 * returns the size of the Binomial
 * @param b is the Binomial
 * @return the size
 */
int sizeBinomial(Binomial *b) {
    return b->size;
}

/**
 * removes a value from the Binomial
 * @param b s the Binomial
 * @param n the node which has the value to be removed
 */
void deleteBinomial(Binomial *b, BinomialNode *n) {
    decreaseKeyBinomial(b,n,NULL);
    (void)extractBinomial(b);
}

/**
 *
 * @param b is the Binomial
 * @param n is the BinomialNode
 * @param v is the new value
 */
void decreaseKeyBinomial(Binomial *b, BinomialNode *n, void *v) {
    n->value = v;
    //bubble up the new value using b's comparator
    BinomialNode *np = bubbleUp(b, n);
    //update b's extreme value pointer, if necessary
    updateExtreme(b,np);
}

/**
 * Function to extract the minimum value from the Binomial
 * @param b is the Binomial
 * @return
 */
void *extractBinomial(Binomial *b) {
    BinomialNode *y = b->extreme;
    //remove y from the root list (place a null in y's spot)
    setDArray(b->rootlist,getDegree(y),NULL);
    //merge the children of y into b's root list (via merge)
    merge(b,y->children);
    b->size--;
    //store y's value
    void *val = y->value;
    free(y);
    //find the new extreme node
    findExtreme(b);
    return val;
}

/**
 * Displays the binomial in level order
 * @param fp is where you're printing to
 * @param b is the Binomial
 */
void displayBinomial(FILE *fp, Binomial *b) {
    if (sizeBinomial(b) == 0) {
        fprintf(fp,"0:\n");
        return;
    }
    //displayBinomialNode(fp,getDArray(b->rootlist,1));
    int i;
    for(i = 0; i < sizeDArray(b->rootlist); i++) {
        BinomialNode *n = getSubHeap(b->rootlist,i);
        if (n != NULL) {
            displayLevelOrder(fp, n);
            fprintf(fp, "----\n");
        }
    }
}

/*********************** Private Functions ***********************/

/**
 * Function to bubble up
 * @param b is the Binomial
 * @param n is the node you're bubbling
 * @return the end result
 */
static BinomialNode *bubbleUp(Binomial *b, BinomialNode *n) {
    //if it's the root or n's value isn't more extreme
    if(n->parent == n || b->compare(n->value,n->parent->value) >= 0)
        return n;
    else {
        b->update(n->value,n->parent);
        b->update(n->parent->value,n);
        void *temp = n->value;
        n->value = n->parent->value;
        n->parent->value = temp;
        return bubbleUp(b,n->parent);
    }
}

static BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y) {
    //if x is more extreme than y, ie lesser because of min heaps
    if (b->compare(x->value,y->value) < 0) {
        int i = getDegree(y);
        setDArray(x->children,i,y);
        y->parent = x;
        return x;
    }
    else {
        int i = getDegree(x);
        setDArray(y->children,i,x);
        x->parent = y;
        return y;
    }
}

/**
 * Function to
 * @param b
 * @param n
 */
static void consolidate(Binomial *b, BinomialNode *n) {
    //set a variable degree to the number of n's children
    int d;
    //while b's root list at index is not empty
    for(d = getDegree(n); getSubHeap(b->rootlist,d) != NULL; d++) {
        //set n to the combination of n and the subtree stored at the index
        n = combine(b,n,getSubHeap(b->rootlist,d));
        //set the slot at index degree to null, since the slot is now empty
        setDArray(b->rootlist,d,NULL);
    }
    //place n at index degree, growing the root list array if necessary
    setDArray(b->rootlist,d,n);
}

/**
 * Function to print the levelOrder
 * @param fp is the output
 * @param n is the first node you want to print
 */
static void displayLevelOrder(FILE *fp, BinomialNode *n) {
    BinomialNode *temp;
    queue *q = newQueue(n->display);
    enqueue(q,n);
    enqueue(q,NULL);
    int level = 0;
    fprintf(fp,"%d: ",level);
    while (sizeQueue(q) != 0) {
        temp = dequeue(q);
        if(sizeQueue(q) == 0) {
            fprintf(fp,"\n");
            break;
        }
        else if (temp == NULL) {
            fprintf(fp,"\n");
            enqueue(q,NULL);
            ++level;
            if (sizeQueue(q) != 1) {
                fprintf(fp,"%d: ",level);
            }
        }
        else {
            displayBinomialNode(fp,temp);
            if (peekQueue(q) != NULL)
                fprintf(fp," ");
            int i;
            for(i = 0; i < sizeDArray(temp->children); i++) {
                enqueue(q,(BinomialNode*)getSubHeap(temp->children,i));
            }
        }
    }
}

/**
 * Function to find the most extreme value in the Binomial used after removing the previous one
 * @param b is the Binomial
 */
static void findExtreme(Binomial *b) {
    b->extreme = NULL;
    int i = 0;
    for(i = 0; i < sizeDArray(b->rootlist); i++) {
        BinomialNode *n = getSubHeap(b->rootlist, i);
        if(n != NULL)
            updateExtreme(b,n);
    }
}

/**
 * Function to easily get the degree (ie how many children)
 * @param n is the node you want the degree of
 * @return the degree
 */
static int getDegree(BinomialNode *n) {
    return sizeDArray(n->children);
}

/**
 * Wrapper function for getDArray to make sure you are returning values correctly
 * @param a is the DArray that it would exist in
 * @param i is the index
 * @return the value in the DArray at that index
 */
static void *getSubHeap(DArray *a,int i) {
    if(i > sizeDArray(a)) {
        fprintf(stderr,"Error in getSubHeap; index greater than the size of the array\n");
        exit(1);
    }
    if (i == sizeDArray(a))
        return NULL;
    return getDArray(a,i);
}

/**
 * Merge the 2
 * @param b is the Binomial
 * @param a is the DArray it origianlly lives in
 */
static void merge(Binomial *b, DArray *a) {
    for (int i = 0; i < sizeDArray(a); i++) {
        ((BinomialNode*)getSubHeap(a,i))->parent = ((BinomialNode*)getSubHeap(a,i));
        consolidate(b,getSubHeap(a,i));
    }
    free(a);
}

/**
 * Function to update the extreme pointer or don't do if the value you passed in is NULL
 * @param b is the Binomial
 * @param n is the node you just inserted
 */
static void updateExtreme(Binomial *b, BinomialNode *n) {
    if(b->extreme == NULL)
        b->extreme = n;
    else if (b->compare(n->value,b->extreme->value) < 0)
        b->extreme = n;
}