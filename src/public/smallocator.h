//
// Created by Limaaron on 08.09.2020.
//

#ifndef SMA_SMA_LLOCATOR_H
#define SMA_SMA_LLOCATOR_H

#include "smalib.h"
#include "datatypes.h"

typedef enum SMA_ErrorType
{
    smaNotInit      = 0x01,
    failAlloc       = 0x02,
    failReAlloc     = 0x04,
    failOutOfMem    = 0x08
} SMA_ErrorType;

MEMORY  SMA_Alloc( dsize size );
MEMORY  SMA_ReAlloc( MEMORY mem, dsize size );
void    SMA_Free( MEMORY mem );

dsize   SMA_GetGlobalAllocated();
dsize   SMA_GetAllocated( MEMORY mem );

dsize   SMA_GetOffset( MEMORY mem );
void    SMA_SetOffset( MEMORY mem,  dsize offset );
void    SMA_MoveOffset( MEMORY mem, dsize size );

#endif // SMA_SMA_LLOCATOR_H
