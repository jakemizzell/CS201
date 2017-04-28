/**
 * test-dll.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is a file to test the dll.c & dll.h files
 */

#include <stdio.h>
#include "dll.h"
#include "integer.h"
#include <time.h>

static void showItems(dll *items) {
    printf("The items are ");
    displayDLL(stdout,items);
    printf(".\n");
}

int main(void) {
    dll *a = newDLL(displayInteger);
    insertDLL(a,0,newInteger(99));
    insertDLL(a,1,newInteger(63));
    removeDLL(a,1);
    insertDLL(a,1,newInteger(19));
    removeDLL(a,0);
    removeDLL(a,0);
    insertDLL(a,0,newInteger(14));
    insertDLL(a,1,newInteger(38));
    insertDLL(a,2,newInteger(52));
    removeDLL(a,1);
    insertDLL(a,2,newInteger(5));
    insertDLL(a,1,newInteger(4));
    insertDLL(a,4,newInteger(19));
    insertDLL(a,1,newInteger(88));
    insertDLL(a,2,newInteger(52));
    insertDLL(a,2,newInteger(41));
    insertDLL(a,4,newInteger(14));
    insertDLL(a,7,newInteger(47));
    removeDLL(a,2);
    insertDLL(a,6,newInteger(27));
    removeDLL(a,7);
    insertDLL(a,5,newInteger(45));
    insertDLL(a,0,newInteger(1));
    insertDLL(a,2,newInteger(21));
    insertDLL(a,9,newInteger(61));
    displayDLL(stdout,a);
    /*dll *items = newDLL(displayInteger);
    int i;
    *//*for (i = 0; i < 10; i ++) {
        insertDLL(items,0,newInteger(i));
    }
    insertDLL(items,3,newInteger(11));
    showItems(items);
    insertDLL(items,7,newInteger(12));
    showItems(items);
    printf("Removed: ");
    displayInteger(stdout,removeDLL(items,3));
    printf("\n");
    showItems(items);
    printf("Removed: ");
    displayInteger(stdout,removeDLL(items,7));
    printf("\n");*//*
    showItems(items);
    printf("Test large input\n");
    clock_t begin = clock();
    dll *a = newDLL(displayInteger);
    for (i = 0; i < 10000; i ++) {
        insertDLL(a,0,newInteger(i));
    }
    for (i = 0; i < 10000; i++) {
        insertDLL(a,sizeDLL(a),newInteger(i));
    }
    for (i = 0; i < 20000; i++) {
        removeDLL(a,0);
    }
    displayDLL(stdout,a);

    printf("\nTest Union\n");
    dll *b = newDLL(displayInteger);
    dll *c = newDLL(displayInteger);
    for (i = 0; i < 100; i ++) {
        if (sizeDLL(b) == 0)
            insertDLL(b,0,newInteger(i));
        else
            insertDLL(b,sizeDLL(b)-1,newInteger(i));
    }
    for (i = 0; i < 100; i ++) {
        if (sizeDLL(c) == 0)
            insertDLL(c, 0, newInteger(i));
        else
            insertDLL(c, sizeDLL(c) - 1, newInteger(i));
    }
    for (i = 0; i < 3; i++) {
        unionDLL(b,c);
    }
    printf("\n");
    displayDLL(stdout,b);
    printf("\n");
    displayDLL(stdout,c);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nSeconds: %f\n", time_spent);*/
    /*dll *items = newDLL(displayInteger);
    showItems(items);
    dll *items = newDLL(displayInteger);
    showItems(items);
    insertDLL(items,0,newInteger(3));                //insert at front
    showItems(items);
    insertDLL(items,sizeDLL(items),newInteger(2));   //insert at back
    showItems(items);
    insertDLL(items,1,newInteger(1));                //insert at middle
    showItems(items);
    insertDLL(items,0,newInteger(5));
    showItems(items);
    printf("The value ");
    displayInteger(stdout,removeDLL(items,3));
    printf(" was removed.\n");
    showItems(items);
    insertDLL(items,sizeDLL(items),newInteger(6));
    showItems(items);
    dll *new = newDLL(displayInteger);
    insertDLL(new,0,newInteger(4));                //insert at front
    showItems(new);
    insertDLL(new,sizeDLL(new),newInteger(2));   //insert at back
    showItems(new);
    unionDLL(items,new);
    showItems(items);
    insertDLL(items,sizeDLL(items),newInteger(8));   //insert at back
    showItems(items);
    int x = getInteger((integer *) getDLL(items,1));
    printf("The first item is %d.\n",x);*/
    return 0;
}