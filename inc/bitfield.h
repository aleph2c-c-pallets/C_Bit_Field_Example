/*=============================================================================
   BitField Project Example
   (c) 2023 BitField Project Example

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

@brief bitfield.h

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
