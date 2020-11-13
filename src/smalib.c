#include "smalib.h"

POINTER moveRight( POINTER ptr, dsize offset )
{
    return POINTER_CAST( POINTER, POINTER_CAST( dpchar, ptr ) + offset );
}

POINTER moveLeft( POINTER ptr, dsize offset )
{
    return POINTER_CAST( POINTER, POINTER_CAST( dpchar, ptr ) - offset );
}
