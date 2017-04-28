/**
 * read.c
 *
 * Written by Jake Mizzell for CS201 Spring 2017
 *
 * This is the reader class used by my bstrees.c for this project
 * It can read the file with words to read into the BST/RBT/VBST
 * It also cleans them up. It also reads in and handles the commands.
 */

#include "read.h"

void readFileVBST (FILE *fp, vbst *a) {
    char *str = obtainString(fp);
    while (!feof(fp)) {
        cleanString(str);
        if (strcmp(str,"") != 0)
            insertVBST(a, newString(str));
        str = obtainString(fp);
    }
}

/**
 * Reads the file and inserts into the RBT
 * @param fp the file you're reading from
 * @param a the RBT
 */
void readFileRBT (FILE *fp, rbt *a) {
    char *str = obtainString(fp);
    while (!feof(fp)) {
        cleanString(str);
        if (strcmp(str,"") != 0)
            insertRBT(a,newString(str));
        str = obtainString(fp);
    }
}

void readCommandsVBST(FILE *fp, FILE *fpOut, vbst *a) {
    char *str = obtainString(fp);
    while (!feof(fp)) {
        cleanString(str);
        //if it is a i you want to get the value as well
        if (strcmp(str, "i") == 0) {
            str = obtainString(fp);
            cleanString(str);
            if (strcmp(str,"") != 0)
                insertVBST(a, newString(str));
        }
        else if (strcmp(str, "d") == 0) {
            str = obtainString(fp);
            cleanString(str);
            deleteVBST(a, newString(str));
        }
        else if (strcmp(str, "f") == 0) {
            str = obtainString(fp);
            cleanString(str);
            fprintf(fpOut, "Frequency of \"%s\": %d\n", str, findVBST(a, newString(str)));
        }
        else if (strcmp(str, "s") == 0)
            displayVBST(fpOut,a);
        else if (strcmp(str, "r") == 0)
            statisticsVBST(a,fpOut);
        str = obtainString(fp);
    }
}

void readCommandsRBT(FILE *fp, FILE *fpOut, rbt *a) {
    char *str = obtainString(fp);
    while (!feof(fp)) {
        cleanString(str);
        //if it is a i you want to get the value as well
        if (strcmp(str, "i") == 0) {
            str = obtainString(fp);
            cleanString(str);
            if (strcmp(str,"") != 0)
                insertRBT(a, newString(str));
        }
        else if (strcmp(str, "d") == 0) {
            str = obtainString(fp);
            cleanString(str);
        }
        else if (strcmp(str, "f") == 0) {
            str = obtainString(fp);
            cleanString(str);
            fprintf(fpOut, "Frequency of \"%s\": %d\n", str, findRBT(a, newString(str)));
        }
        else if (strcmp(str, "s") == 0)
            displayRBT(fpOut,a);
        else if (strcmp(str, "r") == 0)
            statisticsRBT(a,fpOut);
        str = obtainString(fp);
    }
}

/**
 * Uses readToken/readString properly
 * @param fp is the file you're reading from
 * @return str is the word/phrase you want prior to cleaning
 */
char *obtainString(FILE *fp) {
    if (stringPending(fp))
        return readString(fp);
    else
        return readToken(fp);
}

/**
 * Taken from Stack Overflow  post, it cleans strings
 * @param p is the original string
 */
 void cleanString (char *s) {
    char *i = s, *j = s;
    while (*i) {
        if(isspace((unsigned char)*i)) {
            //while it is something to remove get rid of it
            while(isspace((unsigned char)*i) || isdigit((unsigned char)*i) || ispunct((unsigned char)*i))
                i++;
            //add a space because there was at least 1 space
            *j++ = ' ';
        }
        //if not alpha
        else if (!isalpha((unsigned char)*i))
            i++;
        //if uppercase make lower
        else if (isupper((unsigned char)*i)) {
            *j++ = tolower((unsigned char)*i);
            i++;
        }
        //if the same then incriment both
        else if (i == j) {
            i++;
            j++;
        }
        //copy character
        else
            *j++ = *i++;
    }
    //set last value null
    *j = 0;
}