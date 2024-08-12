//
// Created by tobin on 5/31/2024.
//

#include "hstr.h"

#include "../comp/assert.h"
#include "../mem/halloc.h"
#include "../mem/mem_copy.h"
#include "str.h"

/* NOTES:
 * DESIGN ====================================================================
 * This could all be handled using hstr_t
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


u0 hstr_set_end(hstr_t *str, u64 len) {
    assert(str->char_arr != NULL);
    str->end_ptr = str->char_arr + len;
    assert(str->end_ptr != NULL);
}

u64 hstr_len(hstr_t *str) {
    assert(str->char_arr <= str->end_ptr);
    return ((u64) str->end_ptr - (u64) &str->char_arr[0]);
}

u0 internal_hstr_append(hstr_t *base, char *buf, u64 bufLen) {
    if (bufLen == 0) {
        return;
    }

    u64 baseStartLen = hstr_len(base);
    base->char_arr = hrealloc(base->char_arr, baseStartLen + bufLen);
    mem_copy(base->char_arr + baseStartLen, buf, bufLen);
    hstr_set_end(base, baseStartLen + bufLen);
}

u0 hstr_append(hstr_t *base, hstr_t *buf) {
    internal_hstr_append(base, buf->char_arr, hstr_len(buf));
}

u0 hstr_appendCs(hstr_t *base, char *buf) {
    internal_hstr_append(base, buf, internal_C_strlen(buf));
}

u0 hstr_appendu64(hstr_t *base, u64 value) {
    hstr_t *buf = i64_to_hstr(value);
    hstr_append(base, buf);
    hfree(buf);
}

u0 hstr_appendi64(hstr_t *base, i64 value) {
    hstr_t *buf = i64_to_hstr(value);
    hstr_append(base, buf);
    hfree(buf);
}

u0 hstr_free(hstr_t *str) {
    hfree(str->char_arr);
    hfree(str);
}

hstr_t *hstr_fromCs(char *source) {
    hstr_t *str = halloc(sizeof(hstr_t));
    u64 len = internal_C_strlen(source);
    str->char_arr = halloc(len);

    int i = 0;
    for (; i < len; i++) {
        str->char_arr[i] = source[i];
    }

    hstr_set_end(str, len);
    assert(hstr_len(str) == internal_C_strlen(source));

    return str;
}
