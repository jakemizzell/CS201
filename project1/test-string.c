#include <stdio.h>
#include "string.h"

int main (void) {
    string *str = newString("Testing Testing");
    printf("str is %s\n", getString(str));
    setString(str, "test");
    printf("str is now ");
    displayString(stdout, str);
    printf("\n");
    string *str1 = newString("test1");
    string *str2 = newString("test1");
    printf("%d\n",compareString(str1,str2));
    printf("%d\n",compareString(str,str1));
    return 0;
}

