//
// Created by tobin on 7/3/2024.
//

#include "mem_move.h"

#include "salloc.h"

#define MEM_MOVE_MAX_STACK 128

/// Performs a memory move, the same as memmove
/// Supports overlapping buffers
/// \param dest The destination pointer
/// \param src The source pointer
/// \param size The size of the data
/// \return
u0 mem_move(void* dest, void* src, u64 size) {
    u8* tmp = NULL;
    if (size <= MEM_MOVE_MAX_STACK)
    {
        tmp = salloc(size);
    }
    else
    {
        tmp = halloc(size);
    }

    mem_copy(tmp, src, size);
    mem_copy(dest, tmp, size);

    if (size > MEM_MOVE_MAX_STACK)
    {
        hfree(tmp);
    }
}
