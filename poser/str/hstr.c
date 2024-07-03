//
// Created by tobin on 5/31/2024.
//

#include "hstr.h"

#include "../comp/bassert.h"
#include "../mem/halloc.h"
#include "../mem/mem_copy.h"
#include "str.h"

/* NOTES:
 * DESIGN ====================================================================
 * This could all be handled using hstr
 * TODO ======================================================================
 * Implementing chunked strings into this would be nice
 */

u64 internal_C_strlen(char *data) {
    int i = 0;
    while (data[i] != '\0') {
        i++;
    }
    return i;
}


u0 hstr_set_end(hstr *str, u64 len) {
    bassert(str->char_arr != NULL);
    str->end_ptr = str->char_arr + len;
    bassert(str->end_ptr != NULL);
}

u64 hstr_len(hstr *str) {
    bassert(str->char_arr <= str->end_ptr);
    return ((u64) str->end_ptr - (u64) &str->char_arr[0]);
}

u0 internal_hstr_append(hstr *base, char *buf, u64 bufLen) {
    if (bufLen == 0) {
        return;
    }

    u64 baseStartLen = hstr_len(base);
    base->char_arr = hrealloc(base->char_arr, baseStartLen + bufLen);
    mem_copy(base->char_arr + baseStartLen, buf, bufLen);
    hstr_set_end(base, baseStartLen + bufLen);
}

u0 hstr_append(hstr *base, hstr *buf) {
    internal_hstr_append(base, buf->char_arr, hstr_len(buf));
}

u0 hstr_appendCs(hstr *base, char *buf) {
    internal_hstr_append(base, buf, internal_C_strlen(buf));
}

u0 hstr_appendu64(hstr *base, u64 value) {
    hstr *buf = i64_to_hstr(value);
    hstr_append(base, buf);
    hfree(buf);
}

u0 hstr_appendi64(hstr *base, i64 value) {
    hstr *buf = i64_to_hstr(value);
    hstr_append(base, buf);
    hfree(buf);
}

u0 hstr_free(hstr *str) {
    hfree(str->char_arr);
    hfree(str);
}

hstr *hstr_fromCs(char *source) {
    hstr *str = halloc(sizeof(hstr));
    u64 len = internal_C_strlen(source);
    str->char_arr = halloc(len);

    int i = 0;
    for (; i < len; i++) {
        str->char_arr[i] = source[i];
    }

    hstr_set_end(str, len);
    bassert(hstr_len(str) == internal_C_strlen(source));

    return str;
}
