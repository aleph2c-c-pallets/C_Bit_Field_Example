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

@brief bitfield_test.h

  Public interface for the bitfield_test functions.  This package has a CMocka
  requirement.  To install CMocka:

  > sudo apt-get install -y libcmocka-dev

@code{.c}
  // bitfield_test.h basic package usage

  #include <cmocka.h>
  #include "bitfield_test.h"
  // ...
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(bitfield_fnTestBaseline),
    cmocka_unit_test(bitfield_fnTestCreatePacket),
    cmocka_unit_test(bitfield_fnTestValidatePacket),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);

@endcode

==============================================================================*/
#ifndef Bitfield_TEST_H
#define Bitfield_TEST_H
#include "common.h"

void bitfield_fnTestBaseline( void **state );
void bitfield_fnTestCreatePacket( void **state );
void bitfield_fnTestValidatePacket( void **state );

#endif
