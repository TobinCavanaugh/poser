//
// Created by tobin on 7/3/2024.
//

#include "to_str.h"

hstr *i64_to_str_base(i64 val, i8 base) {

    hstr *buf = HSTR("");

    if (val == 0) {
        hstr_appendCs(buf, "0");
        return buf;
    }

    //Set the buf length to 22 characters
    int length = 22;
    int i = 22;

    bool neg = 0;
    if (val < 0) {
        val *= -1;
        neg = 1;
    }

    //add 23 chars, one extra for - sign
    hstr_appendCs(buf, "...-...-...-...-...-...");

    u64 resultLen = 0;
    for (; val && i; --i, val /= base) {
        buf->char_arr[i] = "0123456789abcedf"[val % base];
        resultLen++;
    }

    mem_move(buf->char_arr, buf->char_arr + i + 1, length - i);
    hstr_set_end(buf, length - i);

    if (neg) {
        mem_move(buf->char_arr + 1, buf->char_arr, resultLen);
        buf->char_arr[0] = '-';
        hstr_set_end(buf, resultLen + 1);
    }

    return buf;
}

hstr *i64_to_hstr(i64 val) {
    return i64_to_str_base(val, 10);
}

hstr *u64_to_str(u64 val) {

//    return buf;
}
