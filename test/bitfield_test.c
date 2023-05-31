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

@brief bitfield_test.c

@code{.c}
  // see the bitfield_test.h public header file for package usage examples
@endcode

==============================================================================*/
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/types.h>
#include "bitfield.h"
#include "bitfield_test.h"


void bitfield_fnTestBaseline( void **state ) {
  assert_int_equal(1, 1);
}

void bitfield_fnTestCreatePacket( void **state ) {
  uint32_t ulBigEndianPacket;
  tuPacket ulHostPacket;

  ulBigEndianPacket = BITFIELD_fnCreatePacket(0x03, 0x2, 0xAE);
  ulHostPacket.ulHex = ntohl(ulBigEndianPacket);

  assert_int_equal(ulHostPacket.tzBits.type, 0x03);
  assert_int_equal(ulHostPacket.tzBits.seq_num, 0x2);
  assert_int_equal(ulHostPacket.tzBits.data, 0xAE);
}

void bitfield_fnTestValidatePacket( void **state )
{
  tuPacket ulHostPacket;
  uint32_t ulBigEndianPacket;

  ulBigEndianPacket = BITFIELD_fnCreatePacket(0x03, 0x2, 0xAE);
  assert_true(BITFIELD_fnValidatePacket(ulBigEndianPacket));

  // covert our network stream back into a host uint32_t
  ulHostPacket.ulHex = ntohl(ulBigEndianPacket);
  // break the packet
  ulHostPacket.tzBits.type = 0x01;
  // convert it back into a big endian byte
  ulBigEndianPacket = htonl(ulHostPacket.ulHex);
  assert_false(BITFIELD_fnValidatePacket(ulBigEndianPacket));
}
