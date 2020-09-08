//
// Created by Limaaron on 08.09.2020.
//

#include "smallocator.h"

#include "memoryheader.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"

dsize m_iAllocated = 0;

MEMORY sma_Allocate(dsize size)
{
    dsize totalSize = size + sizeof (MemoryHeader);
    MEMORY mem = malloc(totalSize);

    assert(mem != NULL);
    memset(mem, 0, totalSize);

    MemoryHeader memHeader;
    memHeader.size      = size;
    memHeader.offset    = 0;

    memcpy(mem, &memHeader, sizeof (MemoryHeader));
    mem = move(mem, sizeof (MemoryHeader));

    m_iAllocated += totalSize;

    return mem;
}

MEMORY sma_Realloc(MEMORY mem, dsize size)
{
    mem = move(mem,  -POINTER_CAST(offset, sizeof(MemoryHeader) ));

    MemoryHeader* memHeader = POINTER_CAST(MemoryHeader*, mem);
    m_iAllocated    -= memHeader->size;
    memHeader->size = size;
    m_iAllocated    += size;

    mem = realloc(mem, size);

    return move(mem, sizeof (MemoryHeader));
}

void sma_Free(MEMORY mem)
{
    mem = move(mem, -POINTER_CAST(offset, sizeof(MemoryHeader) ));

    MemoryHeader *memHeader = POINTER_CAST(MemoryHeader*, mem);
    m_iAllocated -= memHeader->size + sizeof (MemoryHeader);

    free(mem);
}

dsize sma_GetGlobalAllocated()
{
    return m_iAllocated;
}

dsize sma_GetAllocated(MEMORY mem)
{
    mem = move(mem, -POINTER_CAST(offset, sizeof(MemoryHeader) ));
    MemoryHeader *memHeader = POINTER_CAST(MemoryHeader*, mem);

    return memHeader->size;
}

dsize sma_GetOffset(MEMORY mem)
{
    mem = move(mem, -POINTER_CAST(offset, sizeof(MemoryHeader) ));
    MemoryHeader *memHeader = POINTER_CAST(MemoryHeader*, mem);

    return memHeader->offset;
}

void sma_SetOffset(MEMORY mem, dsize _offset)
{
    mem = move(mem, -POINTER_CAST(offset, sizeof(MemoryHeader) ));
    MemoryHeader *memHeader = POINTER_CAST(MemoryHeader*, mem);

    if (_offset > memHeader->size)
    {
        printf("[SMA] Error: out of memory");
        exit(EXIT_FAILURE);
    }

    memHeader->offset = _offset;
}

void sma_MoveOffset(MEMORY mem, dsize size)
{
    mem = move(mem, -POINTER_CAST(offset, sizeof(MemoryHeader) ));
    MemoryHeader *memHeader = POINTER_CAST(MemoryHeader*, mem);

    if ((memHeader->offset + size) > memHeader->size)
    {
        printf("[SMA] Error: out of memory");
        exit(EXIT_FAILURE);
    }

    memHeader->offset += size;
}