//
// Created by Limaaron on 08.09.2020.
//

#include "smallocator.h"

#include "memoryheaders.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMA_ErrorMessage( TEXT ) "[SMA] Error: %s", TEXT

static dsize m_uiAllocated  = 0;

static duint *error = NULL;

static AllocFunc    allocMem    = NULL;
static ReAllocFunc  reAllocMem  = NULL;
static FreeFunc     freeMem     = NULL;

void SMA_Error( SMA_ErrorType errorType )
{
#ifdef SMA_MESSAGES
    switch ( errorType )
    {
        case smaNotInit:
            printf( SMA_ErrorMessage( "SMA Not initialized." ) );
            break;
        case failAlloc:
            printf( SMA_ErrorMessage( "failed to allocate memory." ) );
            break;
        case failReAlloc:
            printf( SMA_ErrorMessage( "failed to reallocate memory." ) );
            break;
        case failOutOfMem:
            printf( SMA_ErrorMessage( "out of memory." ) );
        default:
            break;
    }
#endif
    *error |= errorType;
}

void SMA_InitDefault( duint *err )
{
    error = err;

    allocMem    = malloc;
    reAllocMem  = realloc;
    freeMem     = freeMem;
}

void SMA_Init( duint *err,
            AllocFunc   allocator,
            ReAllocFunc reAllocator,
            FreeFunc    free )
{
    error = err;

    allocMem    = allocator;
    reAllocMem  = reAllocator;
    freeMem     = free;
}

MEMORY SMA_Allocate( dsize size )
{
    if (allocMem == NULL)
        SMA_Error( smaNotInit );

    dsize totalSize = size + sizeof( MemoryHeader );
    MEMORY mem = allocMem( totalSize );

    if ( mem == NULL )
        SMA_Error( failAlloc );

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
    if (reAllocMem == NULL)
        SMA_Error( smaNotInit );

    mem = moveLeft( mem, sizeof( MemoryHeader ) );

    MemoryHeader* memHeader = POINTER_CAST( MemoryHeader*, mem );
    m_uiAllocated       -= memHeader->size;
    memHeader->size     = size;
    m_uiAllocated       += size;

    mem = reAllocMem( mem, size );
    if ( mem == NULL )
        SMA_Error( failReAlloc );

    return moveRight( mem, sizeof ( MemoryHeader ) );
}

void SMA_Free( MEMORY mem )
{
    if ( freeMem == NULL )
        SMA_Error( smaNotInit );

    mem = moveLeft( mem, sizeof( MemoryHeader ) );

    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );
    m_uiAllocated -= memHeader->size + sizeof( MemoryHeader );

    freeMem( mem );
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

    if ( _offset > memHeader->size )
        SMA_Error( failOutOfMem );

    memHeader->offset = _offset;
}

void SMA_MoveRightOffset( MEMORY mem, dsize size )
{
    mem = moveLeft( mem, sizeof( MemoryHeader ) );
    MemoryHeader *memHeader = POINTER_CAST( MemoryHeader*, mem );

    if ( ( memHeader->offset + size ) > memHeader->size )
        SMA_Error( failOutOfMem );

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