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

@brief bitfield.h

  Public interface for bitfield.c

@code{.c}
  // bitfield.h package usage example

  #include <stdint.h>
  #include <assert.h>
  #include "bitfield.h"

  int main() {

    // Big Endian Packet that can
    // sent on the wire
    uint32_t ulBigEndianPacket;

    // Initialize the package
    BITFIELD_fnInit();

    // Run the package thread if it needs one
    BITFIELD_fnStart();

    // Set an error bit
    // Set the sequence number to 2
    // Set the data to 0xAE
    // (See tzPacketBitField below for details)
    ulBigEndianPacket = BITFIELD_fnCreatePacket(0x03, 0x02, 0xAE);

    // To validate the packet
    assert(BITFIELD_fnValidatePacket(ulBigEndianPacket));

    return 0;
  }
@endcode

==============================================================================*/
#ifndef BITFIELD_H
#define BITFIELD_H

#include <stdio.h>
#include <arpa/inet.h>
#include "common.h"

typedef struct zPacketBitField
{
  // data (0)
  // acknowledgement (1)
  // control (2)
  // error (3)
  unsigned int type : 4;
  // sequence number of the packet
  unsigned int seq_num : 10;
  // data (2 bytes)
  unsigned int data : 16;
  // XOR of the type seq_num and data
  unsigned int checksum : 2;
} tzPacketBitField;

typedef union zPacket {
  tzPacketBitField tzBits;
  uint32_t ulHex;
} tuPacket;

typedef struct zBitfieldData
{
  uint8_t ucInitialized;
  tuPacket tuPacket;
} tzBitfield;

void BITFIELD_fnInit( void );
void BITFIELD_fnStart( void );
uint32_t BITFIELD_fnCreatePacket(uint8_t ucType, uint16_t uiSequenceNumber, uint16_t uiData);
uint8_t BITFIELD_fnValidatePacket(uint32_t ulPacket);
#endif
