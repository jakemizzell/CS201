/**
 * sll.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is to create a new linked list, insert nodes, remove nodes,
 * join 2 linked list, get the size of a linked list, and display
 * a linked list
**/

#include "sll.h"

sll *newSLL(void (*d)(FILE *,void *)) {
    sll *items = malloc(sizeof(sll));
    if (items == 0) {
        fprintf(stderr,"out of memory");
        exit(-1);
    }
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

void insertSLL(sll *items,int index,void *value) {
    sllnode *newNode = malloc(sizeof(sll));
    newNode->value = value;
    newNode->next = NULL;
    //insert at head
    if (index == 0) {
        newNode->next = items->head;
        items->head = newNode;
        if (items->head->next == NULL) {
            items->tail = newNode;
        }
    }
    //insert at end
    else if (index == items->size) {
        items->tail->next = newNode;
        items->tail = newNode;
    }
    //insert at index
    else {
        sllnode *curr = items->head;
        sllnode *prev = NULL;
        while (index != 0) {
            prev = curr;
            curr = curr->next;
            index--;
        }
        //relink things
        newNode->next = curr;
        prev->next = newNode;
    }
    //update the size of the SLL
    items->size++;
}

void *removeSLL(sll *items,int index) {
    sllnode *curr = malloc(sizeof(sll));
    sllnode *prev;
    sllnode *temp;
    //remove from head
    if (index == 0) {
        //skip what you don't need
        curr = items->head;
        //figure out what you removed
        temp = items->head;
        //join them back together
        curr = curr->next;
        items->head = curr;
        //update the size of the SLL
        items->size--;
        return temp->value;
    }
    //remove from tail
    else if (index == items->size -1) {
        curr = items->head->next;
        prev = items->head;
        int i;
        //loop through list
        for (i = index; curr; i--) {
            //if you reach the index
            if (i == 1) {
                //set the temp to the value
                temp = prev->next;
                //set tail to proper node
                items->tail = prev;
                //skip value
                prev->next = curr->next;
                //update the size of the SLL
                items->size--;
                //return the value
                return temp->value;
            }
            prev = prev->next;
            curr = curr->next;
        }
    }
    //remove from index
    else {
        curr = items->head->next;
        prev = items->head;
        int i;
        //loop through list
        for (i = index; curr; i--) {
            //if you reach the index
            if (i == 1) {
                //set the temp to the value
                temp = prev->next;
                //skip value
                prev->next = curr->next;
                //update the size of the SLL
                items->size--;
                //return the value
                return temp->value;
            }
            //join the list the list
            prev = prev->next;
            curr = curr->next;
        }
    }
    return 0;
}

void unionSLL(sll *recipient,sll *donor) {
    if (recipient->head == 0 && donor->head == 0) {
        return;
    }
    else if (recipient->head == 0 && donor->head != 0) {
        recipient->head = donor->head;
    }
    else {
        if (donor->head == 0) {
            return;
        }
        else {
            recipient->tail->next = donor->head;
        }
    }
    recipient->tail = donor->tail;
    recipient->size += donor->size;
    donor->head = 0;
    donor->tail = 0;
    donor->size = 0;
}

void *getSLL(sll *items,int index) {
    sllnode *curr = malloc(sizeof(sll));
    sllnode *prev, *temp;
    //if it's the head node
    if (index == 0) {
        temp = items->head;
        return temp->value;
    }
    //if the last node
    else if (index == items->size) {
        temp = items->tail;
        return temp->value;
    }
    //if between
    else {
        curr = items->head->next;
        prev = items->head;
        int i;
        //loop through list
        for (i = index; curr; i--) {
            //if you reach the index
            if (i == 1) {
                //set the temp to the value
                temp = prev->next;
                return temp->value;
            }
            //join the list the list
            prev = prev->next;
            curr = curr->next;
        }
    }
    return 0;
}

int sizeSLL(sll *items) {
    return items->size;
}

void displaySLL(FILE *fp,sll *items) {
    if (items == 0) {
        fprintf(fp,"[");
        fprintf(fp,"]");
        return;
    }
    sllnode *curr = malloc(sizeof(sll));
    fprintf(fp,"[");
    curr = items->head;
    int i;
    for(i = 0; curr != NULL; i++) {
        //print a comma if it's not the first one
        if (i > 0)
            fprintf(fp,",");
        items->display(fp,curr->value);
        curr = curr->next;
    }
    fprintf(fp,"]");
}