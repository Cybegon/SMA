#ifndef DATATYPE_GLOBAL_HPP
#define DATATYPE_GLOBAL_HPP

#define KB * 1024
#define MB * 1024 * 1024
#define GB * 1024 * 1024 * 1024

#ifdef CYBEGON_COMPILER_GCC
#   define PACKED_BEGIN
#   define PACKED  __attribute__((__packed__))
#   define PACKED_END
#elif CYBEGON_COMPILER_MSVC
#   define PACKED_BEGIN __pragma(pack(push, 1))
#   define PACKED
#   define PACKED_END __pragma(pack(pop))
#else
#   error PACKED macros are not defined for this compiler
#endif

typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned        uint;
typedef unsigned long   ulong;
typedef char           *pchar;
typedef uchar          *puchar;
typedef const char     *pcchar;

typedef unsigned char   		duint8;    // 8 bit unsigned
typedef short           		dint16;    // 16 bit signed
typedef unsigned short  		duint16;   // 16 bit unsigned
typedef int             		dint32;    // 32 bit signed
typedef signed char     		dint8;     // 8 bit signed
typedef unsigned int   			duint32;   // 32 bit unsigned
typedef long long       		dint64;    // 64 bit signed
typedef unsigned long long      duint64;   // 64 bit unsigned

typedef unsigned char           dBYTE;
#ifdef ARCH_64BITS
typedef duint64          		dsize;
#elif ARCH_32BITS
typedef duint32          		dsize;
#else
#   error Unsupported architecture
#endif
typedef dsize                   offset;
typedef void*           	    POINTER;
typedef POINTER                 MEMORY;

#endif //DATATYPE_GLOBAL_HPP
