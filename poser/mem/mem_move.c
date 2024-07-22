//
// Created by tobin on 7/3/2024.
//

#include "mem_move.h"

/// Performs a memory move, the same as memmove
/// Supports overlapping buffers
/// \param dest The destination pointer
/// \param src The source pointer
/// \param size The size of the data
/// \return
u0 mem_move(void* dest, void* src, u64 size) {
    u8* tmp = halloc(size);

    mem_copy(tmp, src, size);
    mem_copy(dest, tmp, size);

    hfree(tmp);
}
