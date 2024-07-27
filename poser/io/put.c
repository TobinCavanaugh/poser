//
// Created by tobin on 7/2/2024.
//

#include "put.h"

#if SYS_OS == OS_WIN

#include <windows.h>

#endif

static u64 stdout = 1;

POSER_API INLINE u0 set_stdout() {
#if SYS_OS == OS_WIN
    if (rare(stdout == 1 || stdout == 0)) {
        stdout = (u64) GetStdHandle(STD_OUTPUT_HANDLE);
    }
#endif
}


POSER_API INLINE u0 write(u64 handle, byte *data, u64 len) {
    returnif(rare(data == NULL));
    returnif(rare(len == 0));

#if SYS_OS == OS_WIN
    u64 done = 0;
    WriteFile((void *) handle, data, len, (LPDWORD) &done, NULL);
#elif SYS_OS == OS_LINUX
    //TODO Go to coffee shop and write up the asm for this
    //probably tomorrow (the 3rd)
#endif

}

POSER_API INLINE u0 put_n() {
    set_stdout();
    write(stdout, (u8*) "\n", 1);
}

POSER_API INLINE u0 put_s(char *str) {
    set_stdout();
    write(stdout, str, str_len(str));
}

POSER_API INLINE u0 put_sn(char *str) {
    set_stdout();
    put_s(str);
    put_n();
}

POSER_API INLINE u0 put_hs(hstr *str) {
    set_stdout();
    write(stdout, (byte *) str->char_arr, hstr_len(str));
}

POSER_API INLINE u0 put_hsn(hstr *str) {
    set_stdout();
    write(stdout, (byte *) str->char_arr, hstr_len(str));
    put_n();
}

POSER_API INLINE u0 put_i64(i64 val) {
    set_stdout();
    chr buf[25];
    i64_into_buf(buf, val);
    put_s(buf);
}

POSER_API INLINE u0 put_i64n(i64 val) {
    set_stdout();
    put_i64(val);
    put_n();
}

POSER_API INLINE u0 put_u64(u64 val) {
    set_stdout();
    chr buf[25];
    u64_into_buf(buf, val);
    put_s(buf);
}

POSER_API INLINE u0 put_u64n(u64 val) {
    set_stdout();
    put_u64(val);
    put_n();
}
