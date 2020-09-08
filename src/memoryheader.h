//
// Created by Limaaron on 08.09.2020.
//

#ifndef SMA_MEMORYHEADER_H
#define SMA_MEMORYHEADER_H

#include "datatypes.h"

PACKED_BEGIN

typedef struct
{
    dsize size;
    dsize offset;
} PACKED MemoryHeader;

PACKED_END

#endif //SMA_MEMORYHEADER_H
