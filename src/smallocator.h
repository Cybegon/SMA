//
// Created by Limaaron on 08.09.2020.
//

#ifndef SMA_SMALLOCATOR_H
#define SMA_SMALLOCATOR_H

#include "smalib.h"
#include "datatypes.h"

MEMORY  sma_Allocate(dsize size);
MEMORY  sma_Realloc(MEMORY mem, dsize size);
void    sma_Free(MEMORY mem);

dsize   sma_GetGlobalAllocated();
dsize   sma_GetAllocated(MEMORY mem);

dsize   sma_GetOffset(MEMORY mem);
void    sma_SetOffset(MEMORY mem,  dsize offset);
void    sma_MoveOffset(MEMORY mem, dsize size);

#endif //SMA_SMALLOCATOR_H
