//
// Created by tobin on 7/2/2024.
//

#ifndef POSER_MEM_H
#define POSER_MEM_H

#include "mem_copy.h"


byte *halloc(u64 size);

u0 hfree(void *ptr);

byte *hrealloc(void *ptr, u64 size);

#endif //POSER_MEM_H
