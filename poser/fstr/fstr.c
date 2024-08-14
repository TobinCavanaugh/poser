//
// Created by tobin on 3/8/2024.
//

#include "fstr.h"

#define as_ptr(a) ((u64) (a))

#define u8 u8
#define FAILURE (fstr_result) {0}

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

//Internal function prototypes
#pragma region PROTOTYPES

void internal_fstr_insert(fstr *str, u64 index, const char *add, u64 addLen);

void internal_remove_buf(fstr *str, const char *removeBuf, const u64 removeLen);

#pragma endregion PROTOTYPES


u64 fstr_length(const fstr *str) {
    u64 diff = ((as_ptr(str->end) - as_ptr(str->data)) / sizeof(chr));
    return diff;
}

/// Sets the end pointer of the fstr
/// \param str
/// \param newLength
void internal_fstr_set_end(fstr *str, u64 newLength) {
    //Set the end to the address last indexed character of the string
    str->end = as_ptr(&str->data[newLength]);
}

/// Custom String Length function
/// \param buf The string to check
/// \return The length of the string, NOT including the null terminator
u64 internal_C_string_length(const chr *buf) {
    if (USING_WCHAR) {
//        return wcslen(buf);
    } else {
        u64 i = 0;
        while (buf[i] != '\0') {
            i++;
        }

        return i;
    }
}

fstr *fstr_copy(const fstr *str) {
    u64 len = fstr_length(str);
    fstr *new = fstr_from_length(len, '!');
    mem_copy(new->data, str->data, len * sizeof(chr));
    return new;
}

u0 fstr_replace_chr(fstr *str, const chr from, const chr to) {
    u64 len = fstr_length(str);

    u64 i;
    for (i = 0; i < len; i++) {
        if (str->data[i] == from) {
            str->data[i] = to;
        }
    }
}


u0 fstr_remove_at(fstr *str, const u64 index, u64 length) {
    u64 startLen = fstr_length(str);

    if (startLen == 0) {
        return;
    }

    if (index >= startLen) {
        str->error = STR_ERR_IndexOutOfBounds;
        return;
    }

    while (index + length > startLen) {
        length--;

        if (length == 0) {
            str->error = STR_ERR_IndexOutOfBounds;
            return;
        }
    }

    /*
    u64 i, k = 0;
    for (i = 0; i < startLen; i++) {
        if (i < index || i >= (index + length)) {
            str->data[k] = str->data[i];
            k++;
        }
    }
     */

    //    internal_mem_move(str->data + index, str->data + index + length, (startLen - index - length) * sizeof(chr));
    mem_move(str->data + index, str->data + index + length, (startLen - index - length) * sizeof(chr));

    str->data = hrealloc(str->data, (startLen - length) * sizeof(chr));

    internal_fstr_set_end(str, startLen - length);

    //mem_copy approach will not work due to overlapping buffers :(
    //    mem_copy(str->data + index, str->data + index + length, length);
    //    str->data = hrealloc(str->data, (startLen - length) * sizeof(chr));
    //    internal_fstr_set_end(str, startLen - length);

    //    str->data = hrealloc(str->data, k * sizeof(chr));
    //    internal_fstr_set_end(str, k);
}


void internal_compute_index_of_lps(const char *patBuf, int M, int *lps) {
    u64 len = 0;
    u64 i = 1;
    lps[0] = 0;

    while (i < M) {
        if (patBuf[i] == patBuf[len]) {
            len++;
            lps[i] = (int) len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = (int) len;
                i++;
            }
        }
    }
}

/// Returns the index of a substring within the string. Returns to fstr_result.u_val
/// \param str The string to text.
/// \param buf The buffer to check for
/// \param bufLen The length of the buffer
/// \return The result with the index in u_val
fstr_result internal_index_of_sub(const fstr *str, const char *buf, const u64 bufLen) {
    //Tried implementing KMP & BM, both saw worse performance than my brute
    //force optimized version. Brute force with mem_cmp seems like it might
    //be as good as it gets but i'm really not sure... Currently we are getting
    //~4-8ms where C# gets ~1-2ms

    u64 strlen = fstr_length(str);

    if (bufLen > strlen) {
        return FAILURE;
    }

    u64 gi;
    for (gi = 0; gi < strlen; gi++) {
        //Check that our data is within the string. i h
        if (str->data + gi <= str->end) {
            //Do the comparison
            if (mem_cmp(str->data + gi, buf, bufLen) == 0) {
                fstr_result res = (fstr_result) {1};
                res.u_val = gi;
                return res;
            }
        }
    }

    return FAILURE;
}


fstr_result fstr_index_of_C(const fstr *str, char *sub) {
    return internal_index_of_sub(str, sub, internal_C_string_length(sub));
}


fstr_result fstr_index_of(const fstr *str, const fstr *sub) {
    return internal_index_of_sub(str, sub->data, fstr_length(sub));
}


/// Takes a slice of the internal string with the data pointing to the original sliced string. <br/>
/// THIS MEANS THAT ANY CHANGES TO THIS STRINGS DATA WILL AFFECT THE SLICED STRING
/// \param str The string to slice
/// \param start The starting index
/// \param length The length of the slice to take
/// \return The slice which contains a pointer to the strs data
fstr internal_slice(fstr *str, u64 start, u64 length) {
    fstr res = (fstr) {0};
    res.data = str->data + start;
    res.end = (u64) (str->data + start + length);
    return res;
}

/// Replaces any instances of oldBuf with newBuf
/// \param str The string to have contents replaced
/// \param oldBuf The old buffer to look for
/// \param oldLen The length of the old buffer
/// \param newBuf The new buffer to replace the old
/// \param newLen The length of the new buffer
void internal_replace_sub(fstr *str,
                          const chr *oldBuf, const u64 oldLen,
                          const chr *newBuf, const u64 newLen) {
    if (newLen == 0) {
        internal_remove_buf(str, oldBuf, oldLen);
        return;
    }

    u64 initialSize = fstr_length(str) * sizeof(chr);

    //Make a copy of our string, the data points to the same location as our
    //actual str data location
    fstr slice = *str;

    u64 offset = 0;

    i64 diff = 0;

    //Iterate our string
    u8 contains = 1;
    while (contains) {
        //Get the index of our substring (if it exists)
        fstr_result res = internal_index_of_sub(&slice, oldBuf, oldLen);
        contains = res.success;
        u64 index = res.u_val;

        //If we dont contain our substring, we're doneF
        if (!contains) {
            break;
        }

        //Get the distance between our slice start and our string start as the offset
        offset = (as_ptr(slice.data) - as_ptr(str->data));

        if (newLen == oldLen) {
            //Basic copy all the data we can. This is fast AF,  and we are
            //limited by having to expand and shrink the string.
            //                mem_copy(str->data + index + offset, newBuf, newLen);
            mem_copy(str->data + index + offset, newBuf, newLen);
            diff += 0;
        } else if (newLen < oldLen) {
            //Copy in the data
            mem_copy(str->data + index + offset, newBuf, newLen);

            u64 presize = fstr_length(str);
            mem_move(str->data + index + offset + newLen,
                     str->data + index + offset + oldLen,
                     presize - offset - oldLen);

            internal_fstr_set_end(str, presize - (oldLen - newLen));
            diff += (i64) newLen - (i64) oldLen;
            //                mem_move(str->data + index + offset + newLen, str->data + index + offset + oldLen, );
        } else {
            //TODO Do custom implementation of insert and remove for better performance
            fstr_remove_at(str, index + offset, oldLen);
            internal_fstr_insert(str, index + offset, newBuf, newLen);
            diff += (i64) newLen - (i64) oldLen;
        }

        //Remove the substring and replace it
        //            fstr_remove_at(str->data + i, index + offset + i, oldLen - i);
        //            internal_fstr_insert(str->data + i, index + offset + i, newBuf + i, newLen - i);

        //Update the end of our slice
        slice.data = str->data + offset + newLen;
        slice.end = str->end;

        //Do a check to see if we are out of string bounds
        if (slice.data > slice.end) {
            contains = 0;
        }
    }

    if (diff != 0) {
//        u64 size = initialSize - (removed * llabs((i64) newLen - (i64) oldLen));
//TODO this is untested (and wrongish)
        u64 size = initialSize + diff;
        str->data = hrealloc(str->data, size);
        internal_fstr_set_end(str, size);
    }
}

u0 fstr_replace_C(const fstr *str, const chr *oldBuf, const chr *newBuf) {
    internal_replace_sub(str,
                         oldBuf, internal_C_string_length(oldBuf),
                         newBuf, internal_C_string_length(newBuf));
}

u0 fstr_replace(const fstr *str, const fstr *oldBuf, const fstr *newBuf) {
    internal_replace_sub(str,
                         oldBuf->data, fstr_length(oldBuf),
                         newBuf->data, fstr_length(newBuf));
}


void internal_remove_buf(fstr *str, const char *removeBuf, const u64 removeLen) {
    u64 len = fstr_length(str);
    u64 secondary = 0;

    //TODO I wonder if theres a way to remove the alloc...
    //I'm too silly rn to be able to figure it out, but TBH we should be able to just shift our 'i' condition back the length of the remove length, and decrease our len
    //We can also do this non iteratively with mem_copy and stuff, but I'm not too worried if this is a bit slow
    fstr *copy = fstr_copy(str);

    u64 i;
    for (i = 0; i < len; i++) {
        u8 found = 1;

        //Check for the non-existence of the substring removeBuf
        u64 c;
        for (c = 0; c < removeLen; c++) {
            //Do an OOB check,    Do char comparison
            if ((i + c) >= len || copy->data[c + i] != removeBuf[c]) {
                found = 0;
                break;
            }
        }

        //Skip over the stuff we don't want to include
        if (found) {
            i += removeLen - 1;
        }
            //Place our characters into our str
        else {
            str->data[secondary] = copy->data[i];
            secondary++;
        }
    }

    fstr_free(copy);

    internal_fstr_set_end(str, secondary);
}


u0 fstr_remove(const fstr *str, const fstr *buf) {
    internal_remove_buf(str, buf->data, fstr_length(buf));
}

u0 fstr_remove_C(const fstr *str, const chr *buf) {
    internal_remove_buf(str, buf, internal_C_string_length(buf));
}

u0 fstr_append_chr(fstr *str, const chr c) {
    u64 len = fstr_length(str);
    str->data = hrealloc(str->data, (len + 1) * sizeof(chr));

    //Return an error if alloc fails
    if (str->data == NULL) {
        str->error = STR_ERR_hreallocFailed;
        return;
    }

    str->data[len] = c;
    internal_fstr_set_end(str, len + 1);
}

u0 fstr_remove_chr_varargs(fstr *str, u8 num_chars, ...) {
    va_list args;
    va_start(args, num_chars);

    u64 i;
    for (i = 0; i < num_chars; i++) {
        fstr_remove_chr(str, (chr) va_arg(args, int));
    }

    va_end(args);
}

u0 fstr_remove_chr(fstr *str, const chr c) {
    u64 len = fstr_length(str);
    u64 secondary = 0;
    u64 primary;

    //Iterate our string and place our non-c strings into our same string in order
    for (primary = 0; primary < len; primary++) {
        if (str->data[primary] != c) {
            str->data[secondary] = str->data[primary];
            secondary++;
        }
    }

    str->data = hrealloc(str->data, secondary * sizeof(chr));

    internal_fstr_set_end(str, secondary);
}


u64 internal_fstr_count(const fstr *str, const chr *sub, u64 subLength) {
    u64 count = 0;

    fstr slice = *str;

    while (1) {
        fstr_result res = internal_index_of_sub(&slice, sub, subLength);

        if (!res.success) {
            break;
        }

        count++;
        slice.data += res.u_val + subLength;

        if (slice.data > slice.end) {
            break;
        }
    }

    return count;
}


u64 fstr_count_C(const fstr *str, const char *sub) {
    return internal_fstr_count(str, sub, internal_C_string_length(sub));
}


u64 fstr_count(const fstr *str, const fstr *sub) {
    return internal_fstr_count(str, sub->data, fstr_length(sub));
}

u64 fstr_count_chr(const fstr *str, const chr value) {
    u64 len = fstr_length(str);

    u64 count = 0;
    u64 i;
    for (i = 0; i < len; i++) {
        if (str->data[i] == value) {
            count++;
        }
    }
    return count;
}


fstr_result fstr_index_of_chr(fstr *str, char c) {
    u64 i;
    u64 len = fstr_length(str);

    for (i = 0; i < len; i++) {
        if (str->data[i] == c) {
            return (fstr_result) {1, i};
        }
    }

    return FAILURE;
}

fstr *fstr_substr(fstr *str, u64 start, u64 length) {
    u64 len = fstr_length(str);
    if (start >= len) {
        str->error = STR_ERR_IndexOutOfBounds;
        return fstr_from_C("");
    }

    //Create our dummy string
    fstr *sub = fstr_from_length(length, '!');

    //Copy the memory over from our start string
    mem_copy(sub->data, str->data + start, length * sizeof(chr));

    internal_fstr_set_end(sub, length);

    return sub;
}

u0 fstr_set_chr(fstr *str, u64 index, chr c) {
    u64 len = fstr_length(str);
    if (index >= len) {
        str->error = STR_ERR_IndexOutOfBounds;
        return;
    }

    str->data[index] = c;
}

fstr *fstr_from_C(const chr *buf) {
    //Calculate the size of our buffer
    u64 bufSize = internal_C_string_length(buf) * sizeof(chr);

    //halloc our struct
    fstr *str = halloc(sizeof(fstr));

    //halloc our data
    str->data = halloc(bufSize);

    //Reset error
    str->error = STR_ERR_None;

    //Copy in our buffer to our data
    mem_copy(str->data, buf, bufSize);

    //Set the endpoint of our fstr
    str->end = as_ptr(str->data) + as_ptr(bufSize);

    return str;
}


u8 internal_validate_fstr(fstr *str) {
    if (as_ptr(str->data) > str->end) {
        str->error = STR_ERR_INCORRECT_CHAR_POINTER;
        return 0;
    }

    return 1;
}

u0 fstr_free(fstr *str) {
    if (str != NULL) {
        if (str->data != NULL) {
            hfree(str->data);
        }
        hfree(str);
    }
}

void internal_print_chr(const chr *format, const chr printChr) {
//    if (USING_WCHAR) {
//        wprintf(format, printChr);
//    } else if (USING_CHAR) {
//        printf(format, printChr);
//    }
}

u0 fstr_print_chrs(const fstr *str) {
    if (USING_CHAR) {
        u64 i;
        u64 len = fstr_length(str);
        for (i = 0; i < len; i++) {
            internal_print_chr("%c", str->data[i]);
        }
    }
}

u0 fstr_print_chrs_f(const fstr *str, const chr *format) {
    u64 i;
    u64 len = fstr_length(str);
    for (i = 0; i < len; i++) {
        internal_print_chr(format, str->data[i]);
    }
}

u0 fstr_print(const fstr *str) {
    if (str == NULL) {
        return;
    }

    if (USING_CHAR) {
        u64 len = fstr_length(str);
//        fwrite(str->data, sizeof(chr), len, stdout);
        write(get_stdout_handle(), str->data, len);
    }
}


u0 fstr_println(const fstr *str) {
    fstr_print(str);

    if (USING_CHAR) {
        write(get_stdout_handle(), "\n", 2);
    }
}

u0 fstr_print_hex(const fstr *str) {
    u64 len = fstr_length(str);
    u64 i;
    for (i = 0; i < len; i++) {
//        printf("0x%x ", str->data[i]);
    }
}

u0 fstr_print_num(const fstr *str) {
    u64 len = fstr_length(str);
    u64 i = 0;
    for (; i < len; i++) {
//        printf("%d ", str->data[i]);
        put_i64(str->data[i]);
        put_s(" ");
    }
}

/// From William Whyte on stackoverflow
/// https://stackoverflow.com/a/3208376/21769995
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void internal_fstr_print_bin(void *data, u64 len) {
    fstr *str = fstr_from_C("");

    u64 i = 0;

    for (; i < len; i++) {
//        printf(BYTE_TO_BINARY_PATTERN" ", BYTE_TO_BINARY((chr) (data + i)));
    }
}

u0 fstr_print_bin(fstr *str) {
    internal_fstr_print_bin(str->data, fstr_length(str));
}

char *fstr_as_C_heap(const fstr *from) {
    //Get the length of our from string
    u64 len = fstr_length(from);

    //Allocate our new memory, plus one on length for the null terminator
    char *toStr = halloc(len + 1);
    mem_set(toStr, 0, len + 1);

    //Copy our source data over
    mem_copy(toStr, from->data, len * sizeof(chr));

    //Add the null terminator
    toStr[len] = '\0';

    return toStr;
}

u0 fstr_append(fstr *str, const fstr *buf) {
    if (buf == NULL) {
        str->error = STR_ERR_NullStringArg;
        return;
    }

    //Get / calculate the lengths that will be involved
    u64 startLength = fstr_length(str);
    u64 bufLength = fstr_length(buf);
    u64 newLength = startLength + bufLength;

    if (newLength == 0) {
        return;
    }

    //hreallocate our string data to include room for our new buf
    str->data = hrealloc(str->data, newLength * sizeof(chr));

    //Return an error if alloc fails
    if (str->data == NULL) {
        str->error = STR_ERR_hreallocFailed;
        return;
    }

    //Copy the data from our buf onto our str data with an offset of our initial size in bytes
    mem_copy(str->data + startLength * sizeof(chr), buf->data, bufLength * sizeof(chr));

    //Set the end to the pointer to the last character of our new string
    internal_fstr_set_end(str, newLength);
}

u0 fstr_append_C(fstr *str, const chr *buf) {
    if (buf == NULL) {
        str->error = STR_ERR_NullStringArg;
        return;
    }

    //Calculate lengths
    u64 startLen = fstr_length(str);
    u64 bufLen = internal_C_string_length(buf);
    u64 newLen = startLen + bufLen;

    //hrealloc the string
    str->data = hrealloc(str->data, newLen * sizeof(chr));

    //Return an error if hrealloc fails
    if (str->data == NULL) {
        str->error = STR_ERR_hreallocFailed;
        return;
    }

    //Copy the string memory in
    mem_copy(str->data + startLen, buf, bufLen * sizeof(chr));

    //Recalculate the end
    internal_fstr_set_end(str, newLen);
}

fstr *fstr_from_length(u64 length, const chr fill) {
    //Error check
    if (length <= 0) {
        return fstr_from_C("");
    }

    //Create our string
    fstr *str = fstr_from_C("");

    //halloc new string data with the correct size
    str->data = halloc(length * sizeof(chr));

    //Set our error to 0
    str->error = STR_ERR_None;

    //Set all the memory to our fill character
    mem_set(str->data, fill, length * sizeof(chr));

    //Set the end pointer to the last character of our stringF
    //    str->end = as_ptr(&str->data[length]);
    internal_fstr_set_end(str, length);

    return str;
}

u0 fstr_terminate(fstr *str, chr c) {
    fstr_result res = fstr_index_of_chr(str, c);
    if (res.success) {
        str->data = hrealloc(str->data, res.u_val * sizeof(str));
        internal_fstr_set_end(str, res.u_val);
    }
}

fstr *fstr_from_format_C(const char *format, ...) {
/*
    //Varargs stuff
    va_list args;
    va_start(args, format);

    //Calculate the size of the buffer
    u64 size = _vscprintf(format, args);

    //Create the new string, we divide by sizeof chr in case chars are bigger
    //TODO This divide could be wrong
    fstr *str = fstr_from_length(size / sizeof(chr), '!');

    //Write the varargs to the string with the proper format
    vsprintf(str->data, format, args);

    va_end(args);

    return str;
*/
}

u0 fstr_append_format_C(fstr *str, const char *format, ...) {
/*
    if (format == NULL) {
        str->error = STR_ERR_NullStringArg;
        return;
    }

    va_list args;
    va_start(args, format);

    //Get the sizes
    u64 startSize = fstr_length(str) * sizeof(chr);
    u64 addSize = _vscprintf(format, args) / sizeof(chr);
    u64 finalSize = startSize + addSize;

    //hreallocate the data of the string to fit our finalSize
    str->data = hrealloc(str->data, (finalSize + 1) * sizeof(chr));

    //Return an error if alloc fails
    if (str->data == NULL) {
        str->error = STR_ERR_hreallocFailed;
        return;
    }

    //Do our vsprintf to the data, offset by our start size as to write our data to our unneeded stuff
    vsprintf(str->data + startSize, format, args);

    //Set the end of our string
    internal_fstr_set_end(str, finalSize / sizeof(chr));

    va_end(args);
*/
}

void internal_fstr_overwrite(fstr *str, u64 index, char *buf, u64 bufLen) {
    u64 strlen = fstr_length(str);

    u64 finalSize = MAX(strlen, bufLen + index);

    if (finalSize > strlen) {
        str->data = hrealloc(str->data, finalSize * sizeof(chr));
        //        mem_set(str->data + index, '1', finalSize - index);
        mem_set(str->data + strlen, ' ', finalSize - strlen);
    }

    mem_copy(str->data + index, buf, bufLen * sizeof(chr));

    internal_fstr_set_end(str, finalSize);
}

u0 fstr_overwrite_C(fstr *str, u64 index, chr *buf) {
    internal_fstr_overwrite(str, index, buf, internal_C_string_length(buf));
}

u0 fstr_overwrite(fstr *str, u64 index, fstr *buf) {
    internal_fstr_overwrite(str, index, buf->data, fstr_length(buf));
}

u0 fstr_overwrite_format_C(fstr *str, u64 index, chr *format, ...) {
/*
    //Varargs stuff
    va_list args;
    va_start(args, format);

    //Calculate the size of the buffer
    u64 size = _vscprintf(format, args);

    if (size + index < fstr_length(str)) {
        vsprintf(str->data + index, format, args);
    } else {
        //Create the new string, we divide by sizeof chr in case chars are bigger
        //TODO This divide could be wrong
        //TODO Consider making this use stack allocation depending on the size of the string. MAKE SURE TO APPLY TO OTHER FORMAT FUNCTIONS
        //TODO We can also do this in a better way just straight up
        fstr *tmp = fstr_from_length(size / sizeof(chr), '!');

        //Write the varargs to the string with the proper format
        vsprintf(tmp->data, format, args);

        internal_fstr_overwrite(str, index, tmp->data, fstr_length(tmp));

        fstr_free(tmp);
    }

    va_end(args);
*/
}

chr chr_to_invert(chr a) {
    if (USING_CHAR) {
        if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122)) {
            //This works great for well formed non ASCII extended characters
            return (chr) (a ^ 0b00100000);
        }
    } else if (USING_WCHAR) {
        if (chr_is_lower(a)) {
            return towupper(a);
        } else if (chr_is_upper(a)) {
            return towlower(a);
        }
    }

    return a;
}

chr chr_to_lower(chr a) {
    if (chr_is_upper(a)) {
        return chr_to_invert(a);
    }
    return a;
}

chr chr_to_upper(chr a) {
    if (chr_is_lower(a)) {
        return chr_to_invert(a);
    }

    return a;
}

chr internal_chr_is_trim(chr c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

u0 fstr_trim(fstr *str, i8 side) {
    //TODO There must be a better way to do two for loops going in counter directions with same/similar functionality

    //If we are trimming the left side
    if (side <= 0) {
        u64 startTrim = 0;
        u64 i;

        //Go through the string, keep count of any trim characters, if theres a non trim character then we exit and cut that off
        for (i = 0; i < fstr_length(str); i++) {
            chr c = str->data[i];
            if (internal_chr_is_trim(c)) {
                startTrim++;
            } else {
                break;
            }
        }

        fstr_remove_at(str, 0, startTrim);
    }
    if (side >= 0) {
        u64 endTrim = 0;
        u64 i;
        //See (side <= 0)
        for (i = fstr_length(str) - 1; i >= 0; i--) {
            chr c = str->data[i];
            if (internal_chr_is_trim(c)) {
                endTrim++;
            } else {
                break;
            }
        }

        fstr_remove_at(str, fstr_length(str) - endTrim, endTrim);
    }
}


u0 fstr_to_lower(fstr *a) {
    u64 len = fstr_length(a);
    u64 i;
    for (i = 0; i < len; i++) {
        a->data[i] = chr_to_lower(a->data[i]);
    }
}

u0 fstr_to_upper(fstr *a) {
    u64 len = fstr_length(a);
    u64 i;
    for (i = 0; i < len; i++) {
        a->data[i] = chr_to_upper(a->data[i]);
    }
}

u0 fstr_invertcase(fstr *a) {
    u64 len = fstr_length(a);
    u64 i;
    for (i = 0; i < len; i++) {
        chr c = a->data[i];
        a->data[i] = chr_to_invert(c);
    }
}

u8 fstr_equals(fstr *a, fstr *b) {
    if (b == NULL) {
        a->error = STR_ERR_NullStringArg;
        return 0;
    }

    u64 aLen = fstr_length(a);
    u64 bLen = fstr_length(b);

    if (aLen != bLen) {
        return 0;
    }

    u64 i;
    for (i = 0; i < aLen; i++) {
        if (a->data[i] != b->data[i]) {
            return 0;
        }
    }

    return 1;
}

u8 fstr_equals_C(fstr *a, chr *b) {
    u64 alen = fstr_length(a);
    u64 blen = internal_C_string_length(b);

    if (alen != blen) {
        return 0;
    }

    u64 i = 0;
    for (; i < alen; i++) {
        if (a->data[i] != b[i]) {
            return 0;
        }
    }

    return 1;
}


u0 fstr_reverse(fstr *str) {
    u64 len = fstr_length(str);

    if (len == 0 || len == 1) {
        return;
    }

    //TODO Refactor fstr_reverse. It's fine but not quite clean
    if (len == 2) {
        chr tmp = str->data[0];
        str->data[0] = str->data[1];
        str->data[1] = tmp;
        return;
    }

    u64 i = 0;
    u64 j = len;

    for (i; i < len; i++) {
        j--;

        chr tmp = str->data[i];
        str->data[i] = str->data[j];
        str->data[j] = tmp;

        //TODO Refactor fstr_reverse. It's fine but not quite clean
        if (j == i) {
            break;
        }
    }
}

u0 fstr_clear(fstr *str) {
    hfree(str->data);
    str->data = halloc(1);
    mem_set(str->data, 0, 1);

    internal_fstr_set_end(str, 0);
}

/// The internal string insert function
/// \param str
/// \param add
/// \param index
/// \param addLen
void internal_fstr_insert(fstr *str, u64 index, const char *add, u64 addLen) {
    u64 startLen = fstr_length(str);
    u64 finalLen = startLen + addLen;

    if (addLen == 0) {
        return;
    }

    if (index >= finalLen) {
        str->error = STR_ERR_IndexOutOfBounds;
        return;
    }

    str->data = hrealloc(str->data, finalLen * sizeof(chr));

    //Return an error if hrealloc fails
    if (str->data == NULL) {
        str->error = STR_ERR_hreallocFailed;
        return;
    }

    //In the future for debugging / rewriting, draw out memory on paper to make it more understandable

    //Get the buffer size of the right data that will be shifted
    u64 rightBufSize = (startLen - index) * sizeof(chr);

    //Weve gotta write into a temporary buffer cuz otherwise we end up reading then rewriting already written data
    chr *tmp = halloc(rightBufSize);

    //Write the right most data into a temporary buffer
    //    mem_copy(tmp, str->data + index, rightBufSize);
    mem_copy(tmp, str->data + index, rightBufSize);

    //Copy the right most data and place it at its ideal location, leaving
    //some remaining data after u_val with size of add
    //    mem_copy(str->data + (index + addLen), tmp, rightBufSize);
    mem_copy(str->data + (index + addLen), tmp, rightBufSize);

    hfree(tmp);

    //Replace the data after u_val with the size of add with the actual add data
    //    mem_copy(str->data + index, add, addLen * sizeof(chr));
    mem_copy(str->data + index, add, addLen * sizeof(chr));

    internal_fstr_set_end(str, finalLen);
}

u0 fstr_insert(fstr *str, u64 index, const fstr *add) {
    if (add == NULL) {
        str->error = STR_ERR_NullStringArg;
        return;
    }

    internal_fstr_insert(str, index, add->data, fstr_length(add));
}

u0 fstr_insert_C(fstr *str, u64 index, const chr *add) {
    if (add == NULL) {
        str->error = STR_ERR_NullStringArg;
        return;
    }

    internal_fstr_insert(str, index, add, internal_C_string_length(add));
}

fstr **fstr_split(fstr *str) {
}

u0 fstr_pad(fstr *str, u64 targetLength, chr pad, i8 side) {
    u64 currentLen = fstr_length(str);

    if (targetLength <= currentLen) {
        str->error = STR_ERR_IndexOutOfBounds;
        return;
    }

    u64 diff = targetLength - currentLen;

    ///Pad the left side
    if (side < 0) {
        //Pad the left side
        fstr *prePad = fstr_from_length(diff, pad);
        fstr_insert(str, 0, prePad);
        hfree(prePad);
        return;
    }
    ///Pad both sides
    if (side == 0) {
        //Insert the pad on the left
        fstr *left = fstr_from_length(diff / 2, pad);
        fstr_insert(str, 0, left);

        //Pad the remaining right side. This is technically recursive but only ever a depth of 1
        fstr_pad(str, targetLength, pad, 1);

        //hfree the left memory
        hfree(left);
        return;
    }
    ///Pad the right side
    if (side > 0) {
        //Pad the right side
        fstr *prePad = fstr_from_length(diff, pad);

        u64 len = fstr_length(str);
        fstr_insert(str, len, prePad);
        hfree(prePad);

        return;
    }
}

u8 fstr_succeeded(fstr *str) {
    return str->error == 0;
}

u8 internal_fstr_starts_with(char *base, u64 baseLen, char *sub, u64 subLen) {
    if (subLen > baseLen) {
        return 0;
    }

    return (mem_cmp(base, sub, subLen * sizeof(chr)) == 0);
}

u8 fstr_starts_with(fstr *base, fstr *sub) {
    return internal_fstr_starts_with(base->data, fstr_length(base), sub->data, fstr_length(sub));
}

u8 fstr_starts_with_C(fstr *base, chr *sub) {
    return internal_fstr_starts_with(base->data, fstr_length(base), sub, internal_C_string_length(sub));
}

u8 fstr_starts_with_chr(fstr *base, chr sub) {
    if (fstr_length(base) > 0) {
        return (base->data[0] == sub);
    }
    return 0;
}
