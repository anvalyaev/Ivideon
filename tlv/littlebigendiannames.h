#ifndef LITTLEBIGENDIANNAMES_H
#define LITTLEBIGENDIANNAMES_H
#include  <stdint.h>
#include "littlebigendian.h"

typedef int8_t   i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#ifdef BIG_ENDIAN

// Little Endian
typedef LittleEndian<i16> i16le;
typedef LittleEndian<i32> i32le;
typedef LittleEndian<i64> i64le;

typedef LittleEndian<u16> u16le;
typedef LittleEndian<u32> u32le;
typedef LittleEndian<u64> u64le;

// Big Endian
typedef i16 i16be;
typedef i32 i32be;
typedef i64 i64be;

typedef u16 u16be;
typedef u32 u32be;
typedef u64 u64be;

#else

// Little Endian
typedef i16 i16le;
typedef i32 i32le;
typedef i64 i64le;

typedef u16 u16le;
typedef u32 u32le;
typedef u64 u64le;

// Big Endian
typedef BigEndian<i16> i16be;
typedef BigEndian<i32> i32be;
typedef BigEndian<i64> i64be;

typedef BigEndian<u16> u16be;
typedef BigEndian<u32> u32be;
typedef BigEndian<u64> u64be;

#endif
#endif // LITTLEBIGENDIANNAMES_H

