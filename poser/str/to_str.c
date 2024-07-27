//
// Created by tobin on 7/3/2024.
//

#include "to_str.h"

/// Writes the stringified version of the val into the buf. The buffers MINIMUM length should be 23 characters
/// @param buf : The str, this should be a minimum allocated length of
/// @param val : The value to be stringified into the str
u0 i64_into_buf(chr *buf, i64 val) {
    //Im lazy and the code doesnt properly not work for zero values,
    //so i implemented this
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    //the max of a u64 is 22 digits, and we need an extra for the \0
    const u8 digit_count = 22;
    const u8 length = digit_count + 1;
    i8 i = i8l(digit_count);

    const bool neg = (val < 0);
    if (neg) {
        val *= -1;
    }

    const u8 base = 10;
    u64 resultLen = 0;
    for (; val && i; --i, val /= base) {
        buf[i] = "0123456789abcedf"[val % base];
        resultLen++;
    }

    u8 moveOff = 1;
    if (neg) {
        buf[0] = '-';
        moveOff = 0;
        ++resultLen;
    }

    //Shift over to remove any empty spaces
    mem_move(buf + !moveOff, buf + i + 1, length - i);
    buf[resultLen] = '\0';
}

//TODO copy pasting the implementation just sucks.
u0 u64_into_buf(chr *buf, u64 val) {
    //Im lazy and the code doesnt properly not work for zero values,
    //so i implemented this
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    //the max of a u64 is 22 digits, and we need an extra for the \0
    const u8 digit_count = 22;
    const u8 length = digit_count + 1;
    i8 i = i8l(digit_count);

    const u8 base = 10;
    u64 resultLen = 0;
    for (; val && i; --i, val /= base) {
        buf[i] = "0123456789abcedf"[val % base];
        resultLen++;
    }

    //Shift over to remove any empty spaces
    mem_move(buf, buf + i + 1, length - i);
    buf[resultLen] = '\0';
}

#define BUF_SIZE_INTERNAL_23  "!!!!!!!!!!!!!!!!!!!!!!!"

hstr *i64_to_hstr(i64 val) {
    hstr *buf = HSTR(BUF_SIZE_INTERNAL_23);
    i64_into_buf(buf->char_arr, val);
    hstr_set_end(buf, str_len(buf->char_arr));

    return buf;
}


hstr *u64_to_hstr(u64 val) {
    hstr *buf = HSTR(BUF_SIZE_INTERNAL_23);
    u64_into_buf(buf->char_arr, val);
    hstr_set_end(buf, str_len(buf->char_arr));

    return buf;
}
