/**
 * dll.c
 *
 * Written by Jake Mizzell for CS 201 Spring 2017
 *
 * This is to create a new doubly linked list, insert nodes, remove nodes,
 * join 2 linked list, get the size of a linked list, and display
 * a linked list
 */

#include "dll.h"

dll *newDLL(void (*d)(FILE *,void *)) {
    dll *items = malloc(sizeof(dll));
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

void insertDLL(dll *items,int index,void *value) {
    dllnode *newNode = malloc(sizeof(dll));
    dllnode *curr = malloc(sizeof(dll));
    newNode->value = value;
    //insert at head
    if (index == 0) {
        newNode->prev = NULL;
        newNode->next = items->head;
        //if there is things already in the list
        if (items->head) {
            items->head->prev = newNode;
        }
        items->head = newNode;
        if (items->head->next == NULL)
            items->tail = newNode;
    }
        //insert at end
    else if (index == items->size) {
        if (items->tail)
            items->tail->next = newNode;
        newNode->next = NULL;
        newNode->prev = items->tail;
        items->tail = newNode;
    }
        //insert at index starting from tail
    else if (index > (items->size / 2)) {
        curr = items->tail;
        int i;
        for(i=sizeDLL(items)-index; curr; i--) {
            //break if you reach index
            if (i == 1)
                break;
            curr = curr->prev;
        }
        newNode->next = curr;
        newNode->prev = curr->prev;
        //if there is another thing in the list
        if (curr->prev)
            newNode->prev->next = newNode;
        curr->prev = newNode;
    }
    else {
        curr = items->head;
        int i;
        for(i=index; curr; i--) {
            //break if you reach index
            if (i == 1)
                break;
            curr = curr->next;
        }
        newNode->prev = curr;
        newNode->next = curr->next;
        //if there is another thing in the list
        if (curr->next)
            newNode->next->prev = newNode;
        curr->next = newNode;
    }
    items->size++;
}

void *removeDLL(dll *items,int index) {
    dllnode *curr = malloc(sizeof(dll));
    dllnode *temp;
    //if it's the head
    if (index == 0) {
        //set curr to the value
        curr = items->head;
        //set temp to the value
        temp = items->head;
        items->head = curr->next;
        if (items->head)
            items->head->prev = NULL;
        items->size--;
        return temp->value;
    }
        //if removing from tail
    else if (index == items->size-1) {
        curr = items->head;
        int i;
        for(i=0; i < index; i++)
            curr = curr->next;
        //set temp to the value removing
        temp = curr;
        //skip
        curr->prev->next = curr->next;
        //update tail
        items->tail = curr->prev;
        items->size--;
        return temp->value;
    }
        //remove from index starting from tail
    else if (index > (items->size / 2)) {
        curr = items->tail;
        int i;
        for(i=0; i < sizeDLL(items)-index-1; i++)
            curr = curr->prev;
        temp = curr;
        curr->next->prev = curr->prev;
        if (curr->prev)
            curr->prev->next = curr->next;
        items->size--;
        return temp->value;
    }
        //if removing from index
    else {
        curr = items->head;
        int i;
        for(i=0; i < index; i++)
            curr = curr->next;
        temp = curr;
        curr->prev->next = curr->next;
        if (curr->next)
            curr->next->prev = curr->prev;
        items->size--;
        return temp->value;
    }
}

void unionDLL(dll *recipient,dll *donor) {
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
            donor->head->prev = recipient->tail;
        }
    }
    recipient->tail = donor->tail;
    recipient->size += donor->size;
    donor->head = 0;
    donor->tail = 0;
    donor->size = 0;
}

void *getDLL(dll *items,int index) {
    dllnode *curr = malloc(sizeof(dll));
    dllnode *temp;
    //if it's the head node
    if (index == 0) {
        temp = items->head;
        return temp->value;
    }
    else if (index == items->size) {
        temp = items->tail;
        return temp->value;
    }
    else {
        curr = items->head->next;
        int i;
        for(i = index; curr; i--) {
            if (i == 0) {
                temp = curr->prev;
                return temp->value;
            }
            curr = curr->next;
        }
    }
    return 0;
}

int sizeDLL(dll *items) {
    return items->size;
}

void displayDLL(FILE *fp,dll *items) {
    if (items == 0) {
        fprintf(fp,"[");
        fprintf(fp,"]");
        return;
    }
    dllnode *curr = malloc(sizeof(dll));
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
    //debugging for reading back to front
    /*curr = items->tail;
    int i;
    for(i = 0; curr != NULL; i++) {
        //print a comma if it's not the first one
        if (i > 0)
            printf(",");
        items->display(fp,curr->value);
        curr = curr->prev;
    }*/
    fprintf(fp,"]");
}