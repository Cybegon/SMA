#include "smalib.h"

POINTER move(POINTER ptr, offset _offset)
{
    return POINTER_CAST(POINTER, POINTER_CAST(pchar, ptr) + _offset);
}
