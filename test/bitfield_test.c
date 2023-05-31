#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/types.h>
#include "bitfield.h"
#include "bitfield_test.h"


void bitfield_fnTest( void **state ) {
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
