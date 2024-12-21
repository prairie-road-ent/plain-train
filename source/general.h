#include <stdint.h>

#ifndef MECHANISM_CC_GENERAL_H
#define MECHANISM_CC_GENERAL_H

typedef enum {
    __ValueAddressKind__CONSTANT = 0x02,
    __ValueAddressKind__VARIABLE = 0x03,
} ValueAddressKind;

typedef enum {
    __ValueMutabilityKind__STATIC = 0x01,
    __ValueMutabilityKind__CONSTANT = 0x02,
    __ValueMutabilityKind__VARIABLE = 0x03,
} ValueMutabilityKind;

typedef enum {
    __ValueEndianessKind__BIG = 0x01,
    __ValueEndianessKind__LITTLE = 0x02,
} ValueEndianessKind;

typedef uint8_t U8;
typedef int8_t S8;
typedef uint16_t U16;
typedef int16_t S16;
typedef uint32_t U32;
typedef int32_t S32;
typedef uint64_t U64;
typedef int64_t S64;
typedef float IEEE32;
typedef double IEEE64;

typedef char* String;
typedef U8 Byte;
typedef Byte* HeapAllocation;
typedef U8 Bool;

#define BITS_PER_BYTE 8
#define ALLOCATION_INTERNAL_REQUIRED_BYTE_ALIGNMENT_BYTE_SIZE 8
#define true__Bool__STATIC_VALUE 1
#define false__Bool__STATIC_VALUE 0

void printBytes(U8* startAddress, U64 byteCount);
U32 swapEndianU32(U32 value);
U64 swapEndianU64(U64 value);
U32 fourByteStringToU32(String fourByteString);

#endif
