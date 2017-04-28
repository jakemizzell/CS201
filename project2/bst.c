/**
 * bst.c
 *
 * Written by Jake Mizzell for CS201 Spring 2017
 *
 * A BST class. It can insert, swap values to leafs, remove, get stats and other things on a BST
 */


#include "bst.h"
#include "queue.h"


int maxHeight(bstNode*);
int minHeight(bst*);

/**
 * Set up new BST
 * @param d the display function to use
 * @param c the comparator function to use
 * @return the BST
 */
bst *newBST(void (*d)(FILE *,void *),int (*c)(void *,void *)) {
    bst *tree = malloc(sizeof(bst));
    if (tree == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    tree->root = NULL;
    tree->size = 0;
    tree->display = d;
    tree->compare = c;
    return tree;
}

/**
 * psudo code form book pg 294
 * @param tree the bst tree
 * @param v the value you're inserting
 * @return the node you inserted
 */
bstNode *insertBST(bst *tree, void *val) {
    bstNode *y = NULL;
    bstNode *x = tree->root;
    bstNode *n = malloc(sizeof(bstNode));
    n->value = val;
    n->parent = n->right = n->left = NULL;
    while (x != NULL) {
        y = x;
        if (tree->compare(n->value, x->value) < 0)
            x = x->left;
        else
            x = x->right;
    }
    n->parent = y;
    tree->size++;
    //if the tree was empty
    if (y == NULL) {
        n->parent = n;
        tree->root = n;
    }
    else if (tree->compare(n->value, y->value) < 0)
        y->left = n;
    else
        y->right = n;
    return n;
}

/**
 * See if value exist
 * @param tree the bst tree
 * @param v the value you're looking for
 * @return 1 if found otherwise 0
 */
int findBST(bst *tree,void *val) {
    if (tree->root == NULL)
        return 0;
    int found = 0;
    bstNode *n = tree->root;
    while (n != NULL) {
        if (tree->compare(val, n->value) == 0) {
            found = 1;
            break;
        }
        else if (tree->compare(val, n->value) < 0)
            n = n->left;
        else
            n = n->right;
    }
    return found;
}

/**
 * Look for and return node
 * @param tree the BST
 * @param v the value you're looking for
 * @return the node if it exist otherwise 0
 */
bstNode *findBSTNode(bst *tree,void *val) {
    bstNode *n = malloc(sizeof(bstNode));
    //if the tree is empty
    if (tree->root == NULL)
        return 0;
    n = tree->root;
    while (n != NULL) {
        if (tree->compare(val, n->value) == 0)
            return n;
        else if (tree->compare(val, n->value) < 0)
            n = n->left;
        else
            n = n->right;
    }
    return 0;
}

/**
 * Attempt to make the node a leaf
 * @param n the node to swap to leaf
 * @return the node you swapped
 */
bstNode *swapToLeafBSTNode(bstNode *n) {
    void *temp;
    //if it's a leaf
    if (n->left == NULL && n->right == NULL)
        return n;
    else {
        bstNode *np = NULL;
        //if there is a left subtree
        if (n->left != NULL) {
            np = n->left;
            //go as far right as you can go
            while (np->right != NULL)
                np = np->right;
        }
        //there must be a right subtree
        else {
            np = n->right;
            //go as far left as you can go
            while (np->left != NULL)
                np = np->left;
        }
        temp = n->value;
        n->value = np->value;
        np->value = temp;
        return swapToLeafBSTNode(np);
    }
}

/**
 * remove value from BST
 * @param n the value to remove
 */
void pruneBSTNode(bst *b,bstNode *n) {
    b->size--;
    //it's the root
    if (n == b->root) {
        n = NULL;
        b->root = n;
    }
    else {
        if(n->parent->left == n)
            n->parent->left = NULL;
        else
            n->parent->right = NULL;
    }
}

/**
 * gets the size of the BST
 * @param tree is the BST
 * @return the size
 */
int sizeBST(bst *tree) {
    return tree->size;
}
/**
 * Finds the minimum and max height
 * @param tree the BST
 * @param fp the file you're reading to
 */
void statisticsBST(bst *tree,FILE *fp) {
    fprintf(fp, "Nodes: %d\n", sizeBST(tree));
    fprintf(fp, "Minimum depth: %d\n", minHeight(tree));
    fprintf(fp, "Maximum depth: %d\n", maxHeight(tree->root));
}

/**
 * find the max height of the treee
 * @param n is the VBST root node at the start
 * @return the max height
 */
int maxHeight(bstNode *n) {
    if (n == NULL)
        return 0;
    else {
        int lHeight = maxHeight(n->left);
        int rHeight = maxHeight(n->right);
        if (lHeight > rHeight)
            return (lHeight + 1);
        else
            return (rHeight + 1);
    }
}

/**
 * find the min height of the tree
 * @param n is the BST root node at the start
 * @return the min height
 */
int minHeight (bst *b) {
    if (sizeBST(b) == 0)
        return 0;
    //if the root has a null value return 1
    if (b->root->left == NULL || b->root->right == NULL)
        return 1;
    queue *q = newQueue(b->display);
    enqueue(q,b->root);
    enqueue(q,NULL);
    int height = 1;
    while(sizeQueue(q)) {
        bstNode *n = dequeue(q);
        if (n == NULL) {
            enqueue(q,NULL);
            ++height;
        }
        else if (n->left == NULL || n->right == NULL)
            return height;
        else {
            if (n->left != NULL)
                enqueue(q, n->left);
            if (n->right != NULL)
                enqueue(q, n->right);
        }
    }
    return height;
}

/**
 * Display level order
 * @param tree is the BST
 * @param fp is where you're printing the output
 */
void displayBST(FILE *fp, bst *tree) {
    //prints the proper emtpy tree
    if (tree->root == NULL) {
        fprintf(fp, "0:\n");
        return;
    }
    //set up new queue and enqueue root and then NULL
    bstNode *n;
    queue *q = newQueue(tree->display);
    enqueue(q,tree->root);
    enqueue(q,NULL);
    int level = 0;
    fprintf(fp, "%d: ",level);
    while (sizeQueue(q) != 0) {
        n = dequeue(q);
        if (sizeQueue(q) == 0) {
            fprintf(fp, "\n");
            break;
        }
        else if (n == NULL) {
            fprintf(fp, "\n");
            enqueue(q,NULL);
            ++level;
            if (sizeQueue(q) != 1)
                fprintf(fp, "%d: ",level);
        }
        else {
            if (n->left == NULL &&  n->right == NULL)
                fprintf(fp,"=");
            tree->display(fp,n->value);
            fprintf(fp, "(");
            //if there is a parent value print it
            tree->display(fp, n->parent->value);
            fprintf(fp, ")");
            //if it is a left child
            if (tree->compare(n->value, n->parent->value) < 0)
                fprintf(fp, "-l");
            //if a right child
            else if (tree->compare(n->value, n->parent->value) > 0)
                fprintf(fp, "-r");
            //if it was the root
            else
                fprintf(fp, "-");
            if (peekQueue(q) != NULL)
                fprintf(fp, " ");
            if (n->left != NULL)
                enqueue(q, n->left);
            if (n->right != NULL)
                enqueue(q, n->right);
        }
    }
}