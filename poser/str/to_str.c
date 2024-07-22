//
// Created by tobin on 7/3/2024.
//

#include "to_str.h"

hstr* i64_to_str_base(i64 val, i8 base) {
    if (val == 0)
    {
        return HSTR("0");
    }

    //TODO implement using stack allocations once optimized
    //add 23 chars, one extra for - sign
    //note the use of dashes to prevent an unneccessary adding of a dash
    hstr* buf = HSTR("-----------------------");

    //Set the buf length to 22 characters
    const u8 length = hstr_len(buf);
    i8 i = 22;

    const bool neg = (val < 0);
    if (neg)
    {
        val *= -1;
    }

    u64 resultLen = 0;
    for (; val && i; --i, val /= base)
    {
        buf->char_arr[i] = "0123456789abcedf"[val % base];
        resultLen++;
    }

    u8 moveOff = 1;
    if (neg)
    {
        moveOff = 0;
        ++resultLen;
    }


    //Shift over to remove any empty spaces
    mem_move(buf->char_arr + !moveOff, buf->char_arr + i + 1, length - i);
    hstr_set_end(buf, resultLen);

    return buf;
}

hstr* i64_to_hstr(i64 val) {
    return i64_to_str_base(val, 10);
}

hstr* u64_to_hstr(u64 val) {
    //    return buf;
}
