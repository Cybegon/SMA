//
// Created by Limaaron on 08.09.2020.
//

#include "smallocator.h"

#include "memoryheaders.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dsize m_uiAllocated  = 0;

MEMORY SMA_Allocate( dsize size )
{
    dsize totalSize = size + sizeof( MemoryHeader );
    MEMORY mem = malloc( totalSize );

    memset( mem, 0, totalSize );

    MemoryHeader memHeader;
    memHeader.size      = size;
    memHeader.pageSize  = 0;
    memHeader.offset    = 0;

    memcpy( mem, &memHeader, sizeof( MemoryHeader ) );
    mem = moveRight( mem, sizeof( MemoryHeader ) );

    m_uiAllocated += totalSize;

    return mem;
}

MEMORY SMA_ReAlloc( MEMORY mem, dsize size )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );

    MemoryHeader* memHeader = POINTER_CAST( MemoryHeader*, mem );
    m_uiAllocated       -= memHeader->size;
    memHeader->size     = size;
    m_uiAllocated       += size;

    mem = realloc( mem, size );

    return moveRight( mem, sizeof ( MemoryHeader ) );
}

void SMA_Free( MEMORY mem )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );

    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );
    m_uiAllocated -= memHeader->size + sizeof( MemoryHeader );

    free( mem );
}

dsize SMA_GetGlobalAllocated()
{
    return m_uiAllocated;
}

dsize SMA_GetAllocated( MEMORY mem )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    return memHeader->size;
}

dsize SMA_GetOffset( MEMORY mem )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    return memHeader->offset;
}

void SMA_SetOffset( MEMORY mem, dsize _offset )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    memHeader->offset = _offset;
}

void SMA_MoveRightOffset( MEMORY mem, dsize size )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    memHeader->offset += size;
}

void SMA_MoveLeftOffset( MEMORY mem, dsize size )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    if (memHeader->offset < size)
        memHeader->offset = 0;
    else
        memHeader->offset -= size;
}