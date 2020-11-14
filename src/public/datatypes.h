#ifndef DATATYPE_GLOBAL_HPP
#define DATATYPE_GLOBAL_HPP

#define KB(VALUE) VALUE * 1024;
#define MB(VALUE) VALUE * 1024 * 1024;
#define GB(VALUE) VALUE * 1024 * 1024 * 1024;

// If the build system not defined macros
// we try to get them using pre-processor methods
#if !defined(ARCH_64BITS) && !defined(ARCH_32BITS)
#   if defined(__amd64__) || defined(_WIN64) || __SIZEOF_POINTER__ == 8    // 64 bits
#       define ARCH_64BITS
#   elif defined(__x86_64__) || defined(_WIN32) || __SIZEOF_POINTER__ == 4 // 32 bits
#       define ARCH_32BITS
#   else
#       error Unsupported architecture
#   endif
#endif

#if !defined(CYBEGON_COMPILER_GCC) && !defined(CYBEGON_COMPILER_MSVC)
#   if defined(__GNUC__) || defined(__GNUG__)
#       define CYBEGON_COMPILER_GCC
#   elif defined(_MSC_VER)
#       define CYBEGON_COMPILER_MSVC
#   else
#       error Unsupported compiler
#   endif
#endif

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

#ifndef M_PI
#   define M_PI			3.14159265358979323846
#endif

#ifdef SFML_LIBRARY
#   include <System/String.hpp>
#   define TEXT(STRING) sf::String(STRING)
#endif // SFML_LIBRARY

#ifdef __cplusplus
#   define abstract
#   define interface    class
#endif

typedef char            dchar;
typedef unsigned char   duchar;
typedef unsigned short  dushort;
typedef unsigned        duint;
typedef unsigned long   dulong;
typedef dchar          *dpchar;
typedef duchar         *dpuchar;

typedef int             		dint;      // 32 bit signed
typedef unsigned int   			duint;     // 32 bit unsigned

typedef unsigned char   		duint8;    // 8 bit unsigned
typedef short           		dint16;    // 16 bit signed
typedef unsigned short  		duint16;   // 16 bit unsigned
typedef int             		dint32;    // 32 bit signed
typedef signed char     		dint8;     // 8 bit signed
typedef unsigned int   			duint32;   // 32 bit unsigned
typedef long long       		dint64;    // 64 bit signed
typedef unsigned long long   	duint64;   // 64 bit unsigned

typedef unsigned char           dBYTE;
#ifdef ARCH_64BITS
typedef duint64          		dsize;
#elif ARCH_32BITS
typedef duint32          		dsize;
#else
#   error Unsupported architecture
#endif
typedef void*           	    POINTER;
typedef POINTER                 MEMORY;

#endif // DATATYPE_GLOBAL_HPP
