//
// Created by Limaaron on 08.09.2020.
//

#include "smallocator.h"

#include "memoryheaders.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static dsize m_iAllocated = 0;

MEMORY SMA_Allocate( dsize size )
{
    dsize totalSize = size + sizeof( MemoryHeader );
    MEMORY mem = malloc( totalSize );

    if ( mem == NULL )
    {
        printf( "[SMA] Error: Failed to allocate memory" );

        exit( EXIT_FAILURE );
    }
    memset( mem, 0, totalSize );

    MemoryHeader memHeader;
    memHeader.size      = size;
    memHeader.pageSize  = 0;
    memHeader.offset    = 0;

    memcpy( mem, &memHeader, sizeof( MemoryHeader ) );
    mem = moveRight( mem, sizeof( MemoryHeader ) );

    m_iAllocated += totalSize;

    return mem;
}

MEMORY SMA_Realloc( MEMORY mem, dsize size )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );

    MemoryHeader* memHeader = POINTER_CAST( MemoryHeader*, mem );
    m_iAllocated    -= memHeader->size;
    memHeader->size = size;
    m_iAllocated    += size;

    mem = realloc( mem, size );
    if ( mem == NULL )
    {
        printf( "[SMA] Error: Failed to reallocate memory" );

        exit( EXIT_FAILURE );
    }

    return moveRight( mem, sizeof ( MemoryHeader ) );
}

void SMA_Free( MEMORY mem )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );

    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );
    m_iAllocated -= memHeader->size + sizeof( MemoryHeader );

    free( mem );
}

dsize SMA_GetGlobalAllocated()
{
    return m_iAllocated;
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

    if ( _offset > memHeader->size )
    {
        printf( "[SMA] Error: out of memory" );

        exit( EXIT_FAILURE );
    }

    memHeader->offset = _offset;
}

void SMA_MoveOffset( MEMORY mem, dsize size )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    if ( ( memHeader->offset + size ) > memHeader->size )
    {
        printf( "[SMA] Error: out of memory" );

        exit( EXIT_FAILURE );
    }

    memHeader->offset += size;
}