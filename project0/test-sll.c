#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"
#include <time.h>

static void showItems(sll *items) {
    printf("The items are ");
    displaySLL(stdout,items);
    printf(".\n");
}

int main(void) {
    clock_t begin = clock();
    int i;
    printf("\nTest Union\n");
    sll *b = newSLL(displayInteger);
    sll *c = newSLL(displayInteger);
    for (i = 0; i < 100; i ++) {
        if (sizeSLL(b) == 0)
            insertSLL(b,0,newInteger(i));
        else
            insertSLL(b,sizeSLL(b)-1,newInteger(i));
    }
    for (i = 0; i < 100; i ++) {
        if (sizeSLL(c) == 0)
            insertSLL(c, 0, newInteger(i));
        else
            insertSLL(c, sizeSLL(c) - 1, newInteger(i));
    }
    for (i = 0; i < 3; i++) {
        unionSLL(b,c);
    }
    printf("\n");
    displaySLL(stdout,b);
    printf("\n");
    displaySLL(stdout,c);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nSeconds: %f\n", time_spent);
    sll *items = newSLL(displayInteger);
    showItems(items);
    /*sll *items = newSLL(displayInteger);
    showItems(items);
    insertSLL(items,0,newInteger(3));                //insert at front
    showItems(items);
    insertSLL(items,sizeSLL(items),newInteger(2));   //insert at back
    showItems(items);
    insertSLL(items,1,newInteger(1));                //insert at middle
    showItems(items);
    insertSLL(items,1,newInteger(5));
    showItems(items);
    printf("The value ");
    displayInteger(stdout,removeSLL(items,0));       //remove from front
    printf(" was removed.\n");
    showItems(items);
    insertSLL(items,0,newInteger(4));                //insert at front
    showItems(items);
    insertSLL(items,sizeSLL(items),newInteger(6));
    showItems(items);
    sll *new = newSLL(displayInteger);
    insertSLL(new,0,newInteger(4));                //insert at front
    showItems(new);
    insertSLL(new,sizeSLL(new),newInteger(2));   //insert at back
    showItems(new);
    unionSLL(items,new);
    showItems(items);
    showItems(new);
    insertSLL(items,sizeSLL(items),newInteger(8));   //insert at back
    showItems(items);
    int x = getInteger((integer *) getSLL(items,sizeSLL(items)));
    printf("The first item is %d.\n",x);
    showItems(items);*/
    return 0;
}