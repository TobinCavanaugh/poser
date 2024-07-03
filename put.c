//
// Created by tobin on 7/2/2024.
//

#include "put.h"
#include <windows.h>
#include "str.h"
#include "rare.h"
#include "dialect.h"

static HANDLE stdout;

INLINE u0 set_stdout() {
    if (rare(stdout == null)) {
        stdout = GetStdHandle(STD_OUTPUT_HANDLE);
    }
}

INLINE u0 put_n() {
    set_stdout();
    DWORD done = 0;
    WriteFile(stdout, "\n", 1, &done, NULL);
}

INLINE u0 put_s(char *str) {
    set_stdout();
    returnif(str == NULL);
    DWORD done;
    WriteFile(stdout, str, str_len(str), &done, NULL);
}

INLINE u0 put_sn(char *str) {
    set_stdout();
    returnif(str == NULL);
    put_s(str);
    put_n();
}

