//
// Created by tobin on 2024-08-08.
//

#include "thread.h"

thread_t thread_create(u32 (*Function)(void *), byte *args) {
    thread_t *t = (thread_t*) halloc(sizeof(thread_t));
    t->Function = Function;

    u32 thread_id = 0;

    CreateThread(NULL, 0,
                 (LPTHREAD_START_ROUTINE) t->Function,
                 args, 0,
                 ((unsigned long *) &thread_id));

    t->id = thread_id;
}