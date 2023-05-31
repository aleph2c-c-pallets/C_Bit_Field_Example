#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/types.h>
#include "bitfield.h"
#include "bitfield_test.h"


int main() { 
    // initialize the module(s)
    BITFIELD_fnInit();

    // run the application
    BITFIELD_fnStart();

    const struct CMUnitTest tests[] = {
      cmocka_unit_test(bitfield_fnTest),
      cmocka_unit_test(bitfield_fnTestCreatePacket),
      cmocka_unit_test(bitfield_fnTestValidatePacket),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

