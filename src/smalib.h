#ifndef SDA_LIB_HPP
#define SDA_LIB_HPP

#include "datatypes.h"

#ifdef __cplusplus
#   define POINTER_CAST(TYPE, POINTER) reinterpret_cast<TYPE>(POINTER)
#else
#   define POINTER_CAST(TYPE, POINTER) (TYPE) POINTER
#endif

POINTER move(POINTER ptr, offset _offset);

#endif // SDA_LIB_HPP
