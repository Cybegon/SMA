#ifndef SMA_LIB_HPP
#define SMA_LIB_HPP

#include "datatypes.h"

#ifdef __cplusplus
#   include <cstdio>
#   define POINTER_CAST(TYPE, POINTER) ( reinterpret_cast<TYPE>(POINTER) )
#else
#   include <stdio.h>
#   define POINTER_CAST(TYPE, POINTER) ( (TYPE) POINTER )
#endif

#define SMA_PRINT(...) printf(__VA_ARGS__)

POINTER moveRight( POINTER ptr, dsize offset );
POINTER moveLeft( POINTER ptr, dsize offset );

#endif // SMA_LIB_HPP
