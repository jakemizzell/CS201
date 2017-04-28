/**
 * rbt.c
 *
 * Written by Jake Mizzell for CS201 Spring 2017
 *
 * My RBT class. It uses a BST as the basis. You can insert and get stats on it. Deletion isn't tested so wasn't coded
 */

#include "rbt.h"

typedef struct rbtValue {
    void *rVal;
    int freq;
    int color;
    void (*display)(FILE*fp,void*);
    int (*compare)(void*,void*);
}rbtValue;

static rbtValue *newRBTValue(void (*)(FILE *,void *),int (*)(void *,void *));
static void insertionFixUp(bst*, bstNode*);
static bstNode *findUncle(bstNode *n);
static int findColor(bstNode *);
static int checkLinear(bstNode *, bstNode *);
static void rotate(bst *, bstNode*);
static void displayRBTValue(FILE *, void *);
static int rbtComparator(void *, void *);

/**
 * Creates a new RBT
 * @param d the display function
 * @param c the compator function
 * @return the RBT
 */
rbt *newRBT(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    rbt *r = malloc(sizeof(rbt));
    if (r == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    r->tree = newBST(displayRBTValue,rbtComparator);
    r->display = d;
    r->compare = c;
    r->size = 0;
    r->words = 0;
    return r;
}

/**
 * Inserts into the RBT
 * @param r the RBT
 * @param val the value you're inserting
 */
void insertRBT(rbt *r,void *val) {
    rbtValue *rbtV = newRBTValue(r->display,r->compare);
    rbtV->rVal = val;
    //if it's the root incriment size/words, color is already Black and insert it
    if (sizeRBT(r) == 0) {
        r->size++;
        r->words++;
        insertBST(r->tree, rbtV);
        return;
    }
    bstNode *n = findBSTNode(r->tree,rbtV);
    //if it doens't exist
    if (n == 0) {
        r->size++;
        //set node red
        rbtV->color = 1;
        n = insertBST(r->tree, rbtV);
        insertionFixUp(r->tree,n);
    }
    else
        ((rbtValue *)(n->value))->freq++;
    r->words++;
}

/**
 * Gets the freq count on a value
 * @param r the RBT
 * @param val the value you're looking for
 * @return return rbtValue freq
 */
int findRBT(rbt *r,void *val) {
    rbtValue *rbtV = newRBTValue(r->display,r->compare);
    rbtV->rVal = val;
    //look in the bst for that value
    bstNode *n = findBSTNode(r->tree,rbtV);
    //if it wasn't found return 0
    if (n == 0)
        return 0;
    //return the freq
    else
        return ((rbtValue *)(n->value))->freq;
}

/**
 * Deletes the value from the Tree
 * NOTE: Spec was changed to where it's not tested so
 * it does not reorder/recolor the tree properly
 * @param r is the RBT
 * @param val is the value to remove
 */
void deleteRBT(rbt *r, void *val) {
    r = r;
    val = val;
}

/**
 * gets the node count of RBT
 * @param v the RBT
 * @return returns the size
 */
int sizeRBT(rbt *r) {
    return r->size;
}

/**
 * gets the word/phrase count of the VBST
 * @param v is the VBST
 * @return returns the size
 */
int wordsRBT(rbt *r) {
    return r->words;
}

/**
 * Prints the nodes, words, min/max height
 * @param r the RBT
 * @param fp the place you're printing
 */
void statisticsRBT(rbt *r,FILE *fp) {
    fprintf(fp, "Words/Phrases: %d\n", wordsRBT(r));
    statisticsBST(r->tree,fp);
}

/**
 * Prints the RBT
 * @param fp the place you're printing to
 * @param r the RBT
 */
void displayRBT(FILE *fp,rbt *r) {
    displayBST(fp,r->tree);
}

/****************************** private functions ******************************/

/**
 * create new rbtValue
 * @param d is the display passed into rbt
 * @param c is the ocomparator passed into rbt
 * @return the rbtValue
 */
static rbtValue *newRBTValue(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    rbtValue *rbtV = malloc(sizeof(rbtValue));
    if (rbtV == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    rbtV->display = d;
    rbtV->compare = c;
    rbtV->rVal = 0;
    //0 is black 1 is red
    rbtV->color = 0;
    rbtV->freq = 1;
    return rbtV;
}

/**
 * used to recolor after insertion
 * @param b the bst
 * @param n the node you inserted
 */
static void insertionFixUp(bst *b, bstNode *n) {
    bstNode *uncle = NULL, *p = NULL, *gP = NULL, *oldP, *oldN;
    while(1) {
        //if root exit
        if (n == b->root)
            break;
        p = n->parent;
        //if parent is black
        if (!findColor(p))
            break;
        uncle = findUncle(n);
        gP = n->parent->parent;
        //if uncle exist and is red, color parent, uncle, gp, black set n to grandparent
        if (findColor(uncle)) {
            ((rbtValue*)p->value)->color = 0;
            ((rbtValue*)uncle->value)->color = 0;
            ((rbtValue *) gP->value)->color = 1;
            n = gP;
        }
        //uncle must be black or non existant
        else {
            //seeing if they are linear
            if (!checkLinear(n->parent,n)) {
                oldP = p;
                oldN = n;
                //rotate x to parent
                rotate(b,n);
                n = oldP;
                p = oldN;
            }
            //color parent black, gp red, rotate p to gP
            ((rbtValue*)p->value)->color = 0;
            ((rbtValue*)gP->value)->color = 1;
            //rotate parent to grandparent
            rotate(b,p);
            break;
        }
    }
    ((rbtValue*)b->root->value)->color = 0;
}

/**
 * Used to get the color of the node or return 0 if it is NULL
 * @param n is the bstNode you want the color of
 * @returns 1 if red and 0 if black
 */
static int findColor(bstNode *n) {
    if (n == NULL)
        return 0;
    else
        return ((rbtValue*)n->value)->color;
}

/**
 * used to get the uncle
 * @param n the bstNode
 * @return the uncle
 */
bstNode *findUncle(bstNode *n) {
    //if isLeftChild(parent(n)) aka. if the parent is a left child
    if (n->parent->parent->left == n->parent) {
        //return rightChild(grandparent(n))
        return n->parent->parent->right;
    }
    else
        return n->parent->parent->left;
}

/**
 * Sees if 2 values are linear
 * @param p the parent
 * @param n is the node
 * @return 1 if true 0 if false
 */
static int checkLinear(bstNode *p, bstNode *n) {
    //if parent is a left child
    if (p->parent->left == p) {
        //n must be a left child to be linear
        if (n->parent->left == n)
            return 1;
        else
            return 0;
    }
    //parent must be a right child
    else {
        //n must be a right child to be linear
        if (n->parent->right == n)
            return 1;
        else
            return 0;
    }
}

/**
 * used to rotate
 * @param c is the node
 */
static void rotate(bst *b, bstNode *n) {
    bstNode *p = n->parent;
    bstNode *gP = n->parent->parent;
    bstNode *nL = n->left;
    bstNode *nR = n->right;
    //gonna rotate left
    if (p->right == n) {
        n->left = p;
        p->parent = n;
        p->right = nL;
        if (nL != NULL)
            nL->parent = p;
        if (p == b->root) {
            n->parent = n;
            b->root = n;
        }
        else {
            if (gP->left == p)
                gP->left = n;
            else
                gP->right = n;
            n->parent = gP;
        }
    }
    //gonna rotate right
    else {
        n->right = p;
        p->parent = n;
        p->left = nR;
        if (nR != NULL)
            nR->parent = p;
        if (p == b->root) {
            n->parent = n;
            b->root = n;
        }
        else{
            //if p was a right child
            if (gP->right == p)
                gP->right = n;
            else
                gP->left = n;
            n->parent = gP;
        }
    }
}

/**
 * Displays the RBT value, color, and freq
 * @param fp
 * @param val
 */
static void displayRBTValue(FILE *fp, void *val) {
    rbtValue *r = (rbtValue*)val;
    r->display(fp,r->rVal);
    if (r->freq > 1)
        fprintf(fp, "-%d",r->freq);
    if (r->color == 0)
        fprintf(fp,"-B");
    else
        fprintf(fp,"-R");
}

/**
 * the comparator for the rbtValue
 * @param a a val
 * @param b a val
 * @return compare them using the rbtValue compare pointer function
 */
static int rbtComparator (void *a, void *b) {
    rbtValue *x = (rbtValue*)a;
    rbtValue *y = (rbtValue*)b;
    return x->compare(x->rVal,y->rVal);
}