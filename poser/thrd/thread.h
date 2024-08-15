//
// Created by tobin on 2024-08-08.
//
#include "../dialect.h"
#include "../mem/halloc.h"
#include "../comp/assert.h"

#ifndef POSER_THREAD_H
#define POSER_THREAD_H

#if SYS_OS == OS_WIN

#include <windows.h>

#endif


static u64 active_thread_count = 0;

typedef struct {

#if SYS_OS == OS_WIN
    HANDLE _handle;
#endif

    void *result;

    void *(*function)(void *);

    u8 flag_completed: 1;

    u32 id;
} thread_t;


thread_t *thread_create(void *(*Function)(void *), byte *args);

u0 thread_join(thread_t *thread, void **out);

#endif //POSER_THREAD_H
