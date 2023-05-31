/*=============================================================================
  Project/Company-Name
  (c) 2023 Project/Company-Name

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

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
