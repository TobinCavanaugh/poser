//
// Created by tobin on 2024-08-08.
//

#ifndef POSER_THREAD_H
#define POSER_THREAD_H

#include "../poser.h"

typedef struct {
    u32 (*Function)(void *);
    u32 id;
} thread_t;

thread_t thread_create(u32 (*Function)(void *), byte *args);

#endif //POSER_THREAD_H
