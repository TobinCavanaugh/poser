//
// Created by tobin on 7/2/2024.
//

#include "put.h"
#include <windows.h>
#include "../str/str.h"
#include "../comp/rare.h"
#include "../comp/dialect.h"

static u64 stdout = 1;


INLINE u0 set_stdout() {
#if OS == WIN
    if (rare(stdout == 1 || stdout == 0)) {
        stdout = (u64) GetStdHandle(STD_OUTPUT_HANDLE);
    }
#endif
}

INLINE u0 write(u64 handle, byte *data, u64 len) {

    returnif(rare(data == NULL));
    returnif(rare(len == 0));

#if OS == WIN
    u64 done = 0;
    WriteFile((void *) handle, data, len, (LPDWORD) &done, NULL);
#elif OS == LINUX
    //TODO Go to coffee shop and write up the asm for this
    //probably tomorrow (the 3rd)
#endif

}

INLINE u0 put_n() {
    set_stdout();
    write(stdout, "\n", 1);
}

INLINE u0 put_s(char *str) {
    set_stdout();
    write(stdout, str, str_len(str));
}

INLINE u0 put_sn(char *str) {
    set_stdout();
    put_s(str);
    put_n();
}

