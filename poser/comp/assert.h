//
// Created by TobinC on 6/4/2024.
//

#ifndef BASSERT_H
#define BASSERT_H

#include "bint.h"

/* TODO to shrink resulting file size, consider having a generic internal assert
 * function that can be called with args via the assert(n) macros */

#if ENABLE_ASSERTS == 1
#define BASSERT_PASTE_SEQ(seq) #seq
#define BASSERT_CAT_SEQ(x, y) x ## y

/// Assert that when not true, prints out the note, the condition and the URL to the file and line
/// @param cond
#define assertn(cond, note) ({                                                                      \
u8 condVal = (cond);                                                                                 \
if(!condVal) {                                                                                       \
    put_s("\nAssert Failed ------------------------------------------------------------------");\
    put_s("\n\t- Note : ["); put_s(note); put_s("]");                                 \
    put_s("\n\t- Condition : `" BASSERT_PASTE_SEQ(cond) "` is not true. ");                             \
    put_s("\n\t- "); put_s(__FILE__); put_s(":"); put_i64(__LINE__);              \
    sys_exit(10);                                                                                       \
    }                                                                                                \
})

#define assert(cond) assertn(cond, "")

#else
#define bassert(cond) {}
#endif


#endif //BASSERT_H
