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

@brief bitfield.c

@code{.c}
  // see the bitfield.h public header file for package usage examples
@endcode

==============================================================================*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bitfield.h"

/*******************************************************************************
*                         Private Package Scoped Data                          *
*******************************************************************************/
static tzBitfield g_tzBitfieldData;

/*******************************************************************************
*                          Pivate Function Prototypes                          *
*******************************************************************************/
uint8_t bitfield_fnMapTo2Bits(uint8_t ucCheckSum);
uint8_t bitfield_fnCheckSumForBitField(tzPacketBitField tzBitField);
uint8_t bitfield_fnCheckSum(uint8_t ucType, uint16_t uiSequenceNumber, uint16_t uiData);

/*******************************************************************************
*                         Private Function Definitions                         *
*******************************************************************************/

/*=======================================================================*//*!
@brief <!-- bitfield_fnCheckSum -->

  Create an XOR checksum of the given input

@code{.c}
  // example
  ucCheckSum = bitfield_fnCheckSum(0x02, 2, 0xBE);
@endcode

@param
  uint16_t ucType

@param
  uint16_t uiSequenceNumber

@param
  uint16_t uiData

@return
  uint8_t

============================================================================*/
uint8_t bitfield_fnCheckSum(uint8_t ucType, uint16_t uiSequenceNumber, uint16_t uiData)
{
  tzPacketBitField temp;
  uint8_t ucCheckSum;

  // only 4 bits available in type
  ucType &= 0xF;
  temp.type = ucType;

  // only 10 bits available in type
  uiSequenceNumber &= 0x2FF;
  temp.seq_num = uiSequenceNumber;

  temp.data = uiData;
  ucCheckSum = bitfield_fnCheckSumForBitField(temp);
  return ucCheckSum;
}

/*=======================================================================*//*!
@brief <!-- bitfield_fnMapTo2Bits -->

  Mask the first 2 bits (LSB) of a byte

@code{.c}
  // example
  uint8_t ucCheckSum = 0xF;
  ucCheckSum = bitfield_fnMapTo2Bits(ucCheckSum);
  assert(ucCheckSum == 0x3);
@endcode

@param
  uint8_t ucCheckSum

@return
  uint8_t

============================================================================*/
uint8_t bitfield_fnMapTo2Bits(uint8_t ucCheckSum)
{
  return ucCheckSum & 0b11;
}

/*=======================================================================*//*!
@brief <!-- bitfield_fnCheckSumForBitField -->

  Return a checksum for a tzBitField

@param
  tzPacketBitField tzBitField

@code{.c}
  // example, given ulPacket comes from the network
  tuPacket packet;
  packet.ulHex = ntohl(ulPacket);
  assert(bitfield_fnCheckSumForBitField(packet.tzBits));
@endcode

@return
  uint8_t

============================================================================*/
uint8_t bitfield_fnCheckSumForBitField(tzPacketBitField tzBitField)
{
  uint8_t ucCheckSum;
  ucCheckSum = tzBitField.type ^ tzBitField.seq_num ^ tzBitField.data;
  ucCheckSum = bitfield_fnMapTo2Bits(ucCheckSum);
  return ucCheckSum;
}

/*******************************************************************************
*                         Public Function Definitions                          *
*******************************************************************************/

/*=======================================================================*//*!
@brief <!-- BITFIELD_fnInit -->

  Initialize bitfield package. (This is not needed yet)

@code{.c}
  // example
  BITFIELD_fnInit();
@endcode

@param
  void

@return
  void

============================================================================*/
void BITFIELD_fnInit(void)
{
    g_tzBitfieldData.ucInitialized = true;
    return;
}

/*=======================================================================*//*!
@brief <!-- BITFIELD_fnStart -->

  State the bitfield package. (This is not needed yet)

@code{.c}
  // example
  BITFIELD_fnStart();
@endcode

@param
  void

@return
  void

============================================================================*/
void BITFIELD_fnStart(void)
{
    if(g_tzBitfieldData.ucInitialized == false)
    {
       BITFIELD_fnInit();
    }
}

/*=======================================================================*//*!
@brief <!-- BITFIELD_fnCreatePacket -->

  Create a packet that is ready for transmission (organized as Big Endian)

@code{.c}
  // example
  uint32_t ulBigEndianPacket;
  tuPacket ulHostPacket;

  // To create a packet that can be sent over a network socket
  //   type: error
  //   seq_num: 2
  //   data: 0xAE
  ulBigEndianPacket = BITFIELD_fnCreatePacket(0x03, 0x2, 0xAE);

  // To read/process/manipulate this packet on your local hardware
  ulHostPacket.ulHex = ntohl(ulBigEndianPacket);
  assert(ulHostPacket.tzBits.type == 0x3);
  assert(ulHostPacket.tzBits.seq_num == 0x2);
  assert(ulHostPacket.tzBits.data == 0xAE);
@endcode

@param
  uint8_t ucType

@param
  uint16_t uiSequenceNumber

@param
  uint16_t uiData

@return
  uint32_t

============================================================================*/
uint32_t BITFIELD_fnCreatePacket(uint8_t ucType, uint16_t uiSequenceNumber, uint16_t uiData)
{
  tuPacket packet;
  uint8_t ucCheckSum;

  // Calculate the checksum
  ucCheckSum = bitfield_fnCheckSum(ucType, uiSequenceNumber, uiData);

  // Place the bits
  ucType &= 0x7;
  packet.tzBits.type = ucType;
  uiSequenceNumber &= 0x2FF;
  packet.tzBits.seq_num = uiSequenceNumber;
  packet.tzBits.data = uiData;
  packet.tzBits.checksum = ucCheckSum;

  // convert the host bytes to network bytes order
  return htonl(packet.ulHex);

}

/*=======================================================================*//*!
@brief <!-- BITFIELD_fnValidatePacket -->

  Validate a packet to see if its XOR checksum is correct.  The packet is
  assumed to be in Big Endian format.

@code{.c}

  // example
  uint32_t ulBigEndianPacket;
  ulBigEndianPacket = BITFIELD_fnCreatePacket(0x03, 0x2, 0xAE);
  assert(BITFIELD_fnValidatePacket(ulBigEndianPacket));

@endcode

@param
  uint32_t ulPacket

@return
  uint8_t true|false

============================================================================*/
uint8_t BITFIELD_fnValidatePacket(uint32_t ulPacket)
{
  tuPacket packet;
  uint8_t ucResult;
  tzPacketBitField temp;
  uint8_t ucPacketCheckSum;
  uint8_t ucCalculatedCheckSum;

  packet.ulHex = ntohl(ulPacket);
  ucPacketCheckSum = packet.tzBits.checksum;
  temp = packet.tzBits;
  ucCalculatedCheckSum = bitfield_fnCheckSumForBitField(temp);
  ucResult = ucPacketCheckSum == ucCalculatedCheckSum;
  return ucResult;
}
