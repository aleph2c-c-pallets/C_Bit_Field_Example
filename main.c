#include <stdio.h>
#include <sys/types.h>
#include "bitfield.h"


int main() { 
    // initialize the module(s)
    BITFIELD_fnInit();

    // run the application
    BITFIELD_fnStart();

    printf("Hello World!\n");
    return 0;
}