//
// Created by tobin on 2024-08-08.
//

#include "thread.h"


typedef struct
{
    thread_t* thread;
    void* args;
} thread_internal_t;

/// This function that is called in place of calling the thread function
/// directly as to provide functionality such as flag_complete, maintenance
/// of thread count, and allowing for thread internal data to clean itself
/// up.
/// \param data
/// \return
void* thread_wrapper(void* data) {
    thread_internal_t ti = *(thread_internal_t*)data;
    ++active_thread_count;

    /*Call the actual function here*/
    void* retVal = ti.thread->function(ti.args);
    if (retVal != NULL)
    {
        ti.thread->result = retVal;
    }

    ti.thread->flag_completed = 1;

    --active_thread_count;

#if SYS_OS == OS_WIN
    CloseHandle(ti.thread->_handle);
#endif

    hfree(data);
}

u0 thread_join(thread_t* thread, void** out) {
    while (!thread->flag_completed)
    {
    }

    if (out != NULL)
    {
        *out = thread->result;
    }

    hfree(thread);
}

thread_t* thread_create(void*(*Function)(void*), byte* args) {
    thread_t* t = (thread_t*)halloc(sizeof(thread_t));
    t->function = Function;
    t->flag_completed = 0;

    u32 thread_id = 0;

    thread_internal_t* internal = (thread_internal_t*)halloc(sizeof(thread_internal_t));
    internal->thread = t;
    internal->args = args;

#if SYS_OS == OS_WIN
    t->_handle = CreateThread(NULL, 0,
                              (LPTHREAD_START_ROUTINE)thread_wrapper,
                              internal,
                              0,
                              ((unsigned long*)&thread_id));
#endif

#if SYS_OS == OS_LINUX
    assertn( 0 == 1, "NOT IMPLEMENTED");
#endif

    t->id = thread_id;

    return t;
}
