/*=============================================================================
  Project/Company-Name
  (c) 2023 Project/Company-Name

  See LICENSE file

@brief main.c
  This is the main.c file for the debuggable binary

==============================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include "bitfield.h"

int main() {
    // initialize the module(s)
    BITFIELD_fnInit();

    // run the application
    BITFIELD_fnStart();

    printf("bitfield binary ran!\n");
    return 0;
}
