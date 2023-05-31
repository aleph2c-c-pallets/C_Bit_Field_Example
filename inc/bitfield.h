#ifndef Bitfield_H
#define Bitfield_H

#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "common.h"

typedef struct zPacketBitField
{
  // data (0)
  // acknowledgement (1)
  // error (3)
  unsigned int type : 3;
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
