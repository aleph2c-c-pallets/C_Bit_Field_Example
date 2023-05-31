#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bitfield.h"


// static globals
static tzBitfield g_tzBitfieldData;

// prototypes
uint8_t bitfield_fnMapTo2Bits(uint8_t ucCheckSum);
uint8_t bitfield_fnCheckSumForBitField(tzPacketBitField tzBitField);
uint8_t bitfield_fnCheckSum(uint8_t ucType, uint16_t uiSequenceNumber, uint16_t uiData);

// definitions
void BITFIELD_fnInit()
{
    g_tzBitfieldData.ucInitialized = true;
    return;
}

void BITFIELD_fnStart()
{
    if(g_tzBitfieldData.ucInitialized == false)
    {
       BITFIELD_fnInit();
    }
    return;
}


uint8_t bitfield_fnMapTo2Bits(uint8_t ucCheckSum)
{
  return ucCheckSum & 0b11;
}

uint8_t bitfield_fnCheckSumForBitField(tzPacketBitField tzBitField)
{
  uint8_t ucCheckSum;
  ucCheckSum = tzBitField.type ^ tzBitField.seq_num ^ tzBitField.data;
  ucCheckSum = bitfield_fnMapTo2Bits(ucCheckSum);
  return ucCheckSum;
}

uint8_t bitfield_fnCheckSum(uint8_t ucType, uint16_t uiSequenceNumber, uint16_t uiData)
{
  tzPacketBitField temp;
  uint8_t ucCheckSum;

  // only 3 bits available in type
  ucType &= 0x7;
  temp.type = ucType;

  // only 10 bits available in type
  uiSequenceNumber &= 0x2FF;
  temp.seq_num = uiSequenceNumber;

  temp.data = uiData;
  ucCheckSum = bitfield_fnCheckSumForBitField(temp);
  return ucCheckSum;
}

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
