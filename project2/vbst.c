/**
 * vbst.c
 *
 * Written by Jake Mizzell for CS201 Spring 2017
 *
 * This is my VBST class. It uses a BST. It can insert, delete and manipulate the freq of each value in the tree
 */

#include "vbst.h"

typedef struct vbstValue {
    void *vVal;
    int freq;
    void (*display)(FILE*fp,void*);
    int (*compare)(void*,void*);
} vbstValue;

static vbstValue *newVBSTValue(void (*)(FILE *,void *),int (*)(void *,void *));
static void displayVBSTValue(FILE *, void *);
static int vbstComparator(void *,void *);

/**
 * Create new VBST
 * @param d is the display function
 * @param c is the comparator function
 * @return the VBST
 */
vbst *newVBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    vbst *v = malloc(sizeof(vbst));
    if (v == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    v->tree = newBST(displayVBSTValue,vbstComparator);
    v->display = d;
    v->compare = c;
    v->size = 0;
    v->words = 0;
    return v;
}

/**
 * insert into the vanilla BST
 * @param vTree is the vbst
 * @param v is the value to be inserted
 * @return VBST
 */
void insertVBST(vbst *v,void *val) {
    //get the value in the tree if it exist
    vbstValue *vbstV = newVBSTValue(v->display,v->compare);
    vbstV->vVal = val;
    bstNode *n = findBSTNode(v->tree,vbstV);
    //if that node doesn't exist
    if (n==0) {
        v->size++;
        (void)insertBST(v->tree,vbstV);
    }
    //if it did update it's freq
    else
        ((vbstValue *)(n->value))->freq++;
    v->words++;
}

/**
 * Gets the freq count of the tree
 * @param vTree is the VBST
 * @param v is the value you're looking for
 * @return the count
 */
int findVBST(vbst *v, void *val) {
    vbstValue *vbstV = newVBSTValue(v->display,v->compare);
    vbstV->vVal = val;
    //look in the bst for that value
    bstNode *n = findBSTNode(v->tree,vbstV);
    //if it wasn't found return 0
    if (n == 0)
        return 0;
    //return the freq
    else
        return ((vbstValue *)(n->value))->freq;
}

/**
 * deletes the value
 * @param v the vbst
 * @param val the value to remove
 */
void deleteVBST(vbst *v, void *val) {
    vbstValue *vbstV = newVBSTValue(v->display,v->compare);
    vbstV->vVal = val;
    bstNode *n = findBSTNode(v->tree,vbstV);
    //if the value doesn't exist print error message
    if (n == 0) {
        fprintf(stderr, "Value ");
        vbstV->display(stderr, vbstV->vVal);
        fprintf(stderr, " not found\n");
    }
    //it exist so remove it or decrease the freq
    else {
        if (((vbstValue *)(n->value))->freq == 1) {
            n = swapToLeafBSTNode(n);
            pruneBSTNode(v->tree, n);
        }
        else
            ((vbstValue *)(n->value))->freq--;
        //fix the word/size
        v->words--;
        v->size--;
    }
}

/**
 * gets the node count of VBST
 * @param v the VBST
 * @return returns the size
 */
int sizeVBST(vbst *v) {
    return v->size;
}

/**
 * gets the word/phrase count of the VBST
 * @param v is the VBST
 * @return returns the size
 */
int wordsVBST(vbst *v) {
    return v->words;
}

/**
 * Prints the nodes, words, min/max height
 * @param v is the VBST
 * @param fp is the file you're printing to
 */
void statisticsVBST(vbst *v, FILE *fp) {
    fprintf(fp, "Words/Phrases: %d\n", wordsVBST(v));
    statisticsBST(v->tree,fp);
}

/**
 * Prints the VBST
 * @param fp the file you're printing to
 * @param v the VBST
 */
void displayVBST(FILE *fp,vbst *v) {
    displayBST(fp,v->tree);
}


/****************************** Private Functions ******************************/

/**
 * creates a new vbstValue
 * @param d is the display function passed from vbst
 * @param c is the compare function passed form vbst
 * @return the vbst;
 */
static vbstValue *newVBSTValue(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    vbstValue *vbstV = malloc(sizeof(vbstValue));
    if (vbstV == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    vbstV->display = d;
    vbstV->compare = c;
    vbstV->vVal = 0;
    vbstV->freq = 1;
    return vbstV;
}

/**
 * displays the value and freq
 * @param fp is the printing location
 * @param val is the value that you must split
 */
static void displayVBSTValue(FILE *fp, void *val) {
    vbstValue *v = (vbstValue*)val;
    v->display(fp,v->vVal);
    if (v->freq > 1)
        fprintf(fp, "-%d",v->freq);
}

/**
 * the comparator for the vbstValue
 * @param a a val
 * @param b a val
 * @return compare them using the vbstValue compare pointer function
 */
static int vbstComparator(void *a,void *b) {
    vbstValue *x = (vbstValue*)a;
    vbstValue *y = (vbstValue*)b;
    return x->compare(x->vVal,y->vVal);
}