#include "darray.h"
#include <stdlib.h>

typedef struct DArray {
    void **array; //an array of void pointers
    int capacity; //total number of slots
    int size; //number of filled slots
    void (*display)(FILE *,void *);
}DArray;

/**
 * sets up a new dynamic array
 * @param d is the display function to
 * @return
 */
DArray *newDArray(void (*d)(FILE *,void *)) {
    DArray *a = malloc(sizeof(DArray));
    if (a == 0) {
        fprintf(stderr, "out of memory");
        exit(-1);
    }
    a->array = (void *)malloc(sizeof(void));
    a->size = 0;
    a->capacity = 1;
    a->display = d;
    a->array[0] = NULL;
    return a;
}

/**
 * called by setDArray if the index to be set is the size
 * @param a is the DArray
 * @param v is the value to insert
 */
void insertDArray(DArray *a,void *v) {
    //it's full so double it
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->array = realloc(a->array,sizeof(void *)*a->capacity);
    }
    a->array[sizeDArray(a)] = v;
    a->size++;
}

/**
 * remove the last value from the array
 * @param a is the DArray
 * @return the value you remove
 */
void *removeDArray(DArray *a) {
    //the array is empty
    if (a->size == 0)
        return NULL;
    void *v = a->array[sizeDArray(a) - 1];
    a->array[sizeDArray(a) - 1] = NULL;
    a->size--;
    //reduce by half if size is less than 25% of capacity
    if (a->capacity != 1 && (a->size < (a->capacity/4))) {
        a->capacity /= 2;
        a->array = realloc(a->array, sizeof(void *)*a->capacity);
    }
    return v;
}
/**
 * get the value at the index
 * @param a is the DArray
 * @param index is the index you want
 * @return return the value there
 */
void *getDArray(DArray *a,int index) {
    return a->array[index];
}

/**
 * used to add values to the array
 * @param a is the DArray
 * @param index is where you want to place it
 * @param value is the value to be inserted
 */
void setDArray(DArray *a,int index,void *value) {
    if (index == a->size)
        return insertDArray(a,value);
    else
        a->array[index] = value;
}


/**
 * get the size of the array
 * @param a is the DArray
 * @return the size
 */
int sizeDArray(DArray *a) {
    return a->size;
}

void displayDArray(FILE *fp,DArray *a) {
    int i = 0;
    fprintf(fp,"[");
    for(i = 0; i < a->size; i++) {
        a->display(fp,a->array[i]);
        if (i < sizeDArray(a) - 1)
            fprintf(fp,",");
    }
    fprintf(fp,"][%d]",a->capacity - a->size);
}