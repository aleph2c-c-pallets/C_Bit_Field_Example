/*=============================================================================
  MIT License

  (c) 2023 Project/Company-Name

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

@brief main.c
  This is the main.c file for the ctest binary

==============================================================================*/
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "bitfield.h"
#include "bitfield_test.h"

int main() {

    // Initialize the module(s)
    BITFIELD_fnInit();

    // Run the application
    BITFIELD_fnStart();

    const struct CMUnitTest tests[] = {
      cmocka_unit_test(bitfield_fnTestBaseline),
      cmocka_unit_test(bitfield_fnTestCreatePacket),
      cmocka_unit_test(bitfield_fnTestValidatePacket),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

