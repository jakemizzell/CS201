#include <stdio.h>
#include "real.h"

int main(int argc,char **argv) {
    printf("Real tester\n");
    real *x = newReal(2.245);
    printf("x is %f\n",getReal(x));
    setReal(x,-1.345);
    printf("x is now ");
    displayReal(stdout,x);
    printf("\n");
    return 0;
}

