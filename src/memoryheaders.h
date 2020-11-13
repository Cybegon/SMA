//
// Created by Limaaron on 08.09.2020.
//

#ifndef SMA_MEMORY_HEADERS_H
#define SMA_MEMORY_HEADERS_H

#include "datatypes.h"

PACKED_BEGIN

typedef enum
{
    PS_Free         = 0x00,
    PS_Allocated    = 0x3F,
    PS_Root         = 0x7F
} PACKED PageStatus;

typedef struct
{
    dsize size;
    dsize pageSize;
    dsize offset;
} PACKED MemoryHeader;

typedef struct
{
    POINTER             prevPage;
    POINTER             nextPage;
    PageStatus          status;
    dsize               offset;
} PACKED PageHeader;

PACKED_END

#endif //SMA_MEMORY_HEADERS_H
