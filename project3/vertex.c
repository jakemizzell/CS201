#include "vertex.h"

Vertex *newVertex(int val) {
    Vertex *v = (Vertex*)malloc(sizeof(Vertex));
    v->value = val;
    v->prev = NULL;
    v->distance = INT_MAX;
    v->steps = 0;
    v->visited = 0;
    v->neighbors = newDArray(displayInteger);
    v->node = NULL;
    return v;
}

Neighbor *newNeighbor(int v, int w) {
    Neighbor *n = (Neighbor*)malloc(sizeof(Neighbor));
    n->v = newVertex(v);
    n->weight = w;
    return n;
}

/**
 * Look for a vertex
 * @param v is the vertex
 * @param a is the list it would be in
 * @return the vertex if it exist, 0 otherwise
 */
Vertex *getVertex(int val,DArray *a) {
    int i;
    for (i = 0; i < sizeDArray(a); i++) {
        Vertex *v = getDArray(a,i);
        if (v->value == val)
            return v;
    }
    return NULL;
}

/**
 * Funtiont to get the Neighbor
 * @param val is the value you're looking for
 * @param a is the DArray it would be in
 * @return the neighbor if exist, else 0
 */
Neighbor *getNeighbor(int val, DArray *a) {
    int i;
    for (i = 0; i < sizeDArray(a); i++) {
        Neighbor *n = getDArray(a,i);
        if (n->v->value == val)
            return n;
    }
    return 0;
}


Vertex *getMinVertex(DArray *a) {
    if (sizeDArray(a) == 0)
        return NULL;
    //see if any are less
    Vertex *min = getDArray(a,0);
    for(int i = 1; i < sizeDArray(a); i++) {
        Vertex *spot = getDArray(a,i);
        if (spot->value < min->value)
            min = spot;
    }
    return min;
}

Vertex *getNeighborVertex(DArray *list,Neighbor *n) {
    Vertex *v = getVertex(n->v->value,list);
    return v;
}

int getWeight(Vertex *v) {
    Neighbor *n = getNeighbor(v->prev->value,v->neighbors);
    if (n != 0)
        return n->weight;
    else
        return 0;
}
/**
 * Funtion to insertVertex
 * @param v1 is the vertex
 * @param v2 is the vertex it's conected to
 * @param w is the weight
 * @param list is the list the vertex are in
 */
void insertVertex(int v1, int v2, int w, DArray *list) {
    Vertex *tempV = getVertex(v1,list);
    //if it doesn't exist
    if (tempV == NULL) {
        Vertex *v = newVertex(v1);
        Neighbor *n = newNeighbor(v2,w);
        setDArray(v->neighbors,sizeDArray(v->neighbors),n);
        setDArray(list,sizeDArray(list),v);
    }
    //if it does exist
    else {
        Neighbor *tempN = getNeighbor(v2,tempV->neighbors);
        //if the neighbor already exist
        if (tempN == NULL) {
            Neighbor *n = newNeighbor(v2, w);
            setDArray(tempV->neighbors, sizeDArray(tempV->neighbors), n);
        }
        //if the new weight is larger than the old
        else if (tempN->weight > w)
            tempN->weight = w;
    }
}

/**
 * Funtion to read the file and fill up the adjacency list
 * @param fp is the file to be read
 * @param a is the adjList that you're filling
 */
void fillList(FILE *fp, DArray *list) {
    char c = readChar(fp);
    //fill the list as long as there is more
    while (c != EOF) {
        ungetc(c, fp);
        edge *e = readFile(fp);
        //printf("%d %d %d\n",e->vertex1,e->vertex2, e->weight);
        //insert the first vertex in the second vertex neighbors list
        insertVertex(e->vertex1,e->vertex2,e->weight,list);
        //insert the 2nd vertex in the first vertex neighbors list
        insertVertex(e->vertex2,e->vertex1,e->weight,list);
        free(e);
        c = readChar(fp);
    }
}

void printList(FILE *fp,DArray *list) {
    int i, j;
    //print out the vertex
    for (i = 0; i < sizeDArray(list); i++) {
        Vertex *v = getDArray(list, i);
        displayVertex(fp,v);
        fprintf(fp,": ");
        //print out the neighbors
        for(j = 0; j < sizeDArray(v->neighbors); j++) {
            Neighbor *n = getDArray(v->neighbors,j);
            displayVertex(fp,n->v);
            fprintf(fp,"(");
            //displayWeight(fp,n);
            fprintf(fp,")");
            //fprintf(fp,"Dis: %d",v->distance);
            if ((sizeDArray(v->neighbors) - j) > 1)
                fprintf(fp,"->");
        }
        fprintf(fp,"\n");
    }
}

void displayVertex(FILE *fp, void *val) {
    Vertex *v = (Vertex*)val;
    fprintf(fp,"%d",v->value);
    if (v->prev != NULL && v->prev != v) {
        fprintf(fp, "(%d)%d", v->prev->value,v->distance);

        //displayWeight(fp,v);
    }
}

void displayWeight(FILE *fp, Vertex *v) {
    int weight = getWeight(v);
    if (weight != 0)
        fprintf(fp,"%d",weight);
}

/**
 * Funtion to read the file and store things in an edge structure
 * @param fp is the file
 * @return the edge
 */
edge *readFile(FILE *fp) {
    edge *e = (edge*)malloc(sizeof(edge));
    e->vertex1 = readInt(fp);
    e->vertex2 = readInt(fp);
    char *temp = readToken(fp);
    //if there isn't a given weight
    if (!strcmp(temp,";"))
        e->weight = 1;
    else {
        e->weight = atoi(temp);
        temp = readToken(fp);
    }
    free(temp);
    return e;
}

int compareVertex(void *a, void *b) {
    if (a == NULL && b == NULL)
        return 0;
    else if (a == NULL)
        return -1;
    else if (b == NULL)
        return 1;
    Vertex *x = (Vertex*)a;
    Vertex *y = (Vertex*)b;
    if (x->distance == y->distance) {
        if (x->value < y->value)
            return -1;
        else
            return 1;
    }
    else if (x->distance < y->distance)
        return -1;
    else
        return 1;
}

void updateVertex(void *val, BinomialNode *n) {
    Vertex *x = (Vertex*)val;
    x->node = n;
}