#include "general.h"
#include <stdio.h>

void printBytes(U8* startAddress, U64 byteCount)
{
  U8* currentAddress;
  for (U64 byteIndex = 0; byteIndex < byteCount; byteIndex++)
  {
    currentAddress = startAddress + byteIndex;
    printf("%02x ", *currentAddress);
  }
  printf("\n");
}

U32 swapEndianU32(U32 value)
{
  return ((value >> 24) & (U32)0x000000FF) |
         ((value >> 8) & (U32)0x0000FF00) |
         ((value << 8) & (U32)0x00FF0000) |
         ((value << 24) & (U32)0xFF000000);
}

U64 swapEndianU64(U64 value)
{
  return ((value >> 56) & (U64)0x00000000000000FF) |
         ((value >> 40) & (U64)0x000000000000FF00) |
         ((value >> 24) & (U64)0x0000000000FF0000) |
         ((value >> 8) & (U64)0x00000000FF000000) |
         ((value << 8) & (U64)0x000000FF00000000) |
         ((value << 24) & (U64)0x0000FF0000000000) |
         ((value << 40) & (U64)0x00FF000000000000) |
         ((value << 56) &(U64) 0xFF00000000000000);
}

U32 fourByteStringToU32(String fourByteString)
{
  U8 inputStringLength = 4;
  U32 byteResult = 0;
  for (U8 charIndex = 0; charIndex < inputStringLength; charIndex++)
  {
    byteResult |= (U8)fourByteString[charIndex] << (BITS_PER_BYTE * ((inputStringLength - 1) - charIndex));
  }
  return byteResult;
}
