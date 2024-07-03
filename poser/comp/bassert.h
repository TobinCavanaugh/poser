//
// Created by TobinC on 6/4/2024.
//

#ifndef BASSERT_H
#define BASSERT_H

#include "bint.h"

#ifdef _DEBUG
#define PASTE_SEQ(seq) #seq
#define CAT_SEQ(x, y) x ## y

/// Assert that when not true, prints out the note, the condition and the URL to the file and line
/// @param cond
#define bassertn(cond, note) ({                                                                      \
u8 condVal = (cond);                                                                                 \
if(!condVal) {                                                                                       \
    put_sn("\nAssert Failed ------------------------------------------------------------------");\
    put_sn("\n\t- Note : ["); put_sn(note); put_sn("]");                                 \
    put_sn("\n\t- Condition : `" PASTE_SEQ(cond) "` is not true. ");                             \
    put_sn("\n\t- "); put_sn(__FILE__); put_sn(":"); io_printu64(__LINE__);              \
    _exit(10);                                                                                       \
    }                                                                                                \
})

#define bassert(cond) bassertn(cond, "")

#else
#define bassert(cond) {}
#endif


#endif //BASSERT_H
