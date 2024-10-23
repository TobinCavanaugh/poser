//
// Created by tobin on 2024-10-01.
//

#include "write.h"

#if SYS_OS == OS_WIN
#include <windows.h>
#include <shlwapi.h>
#endif


result_file_t file_open(char* path, F_OPEN_TYPES type) {
    bool exists = PathFileExistsA(path);

    if (type & F_OPEN_C && type & F_OPEN_D)
    {
        return (result_file_t){(file_t){0}, 0, 2, 0};
    }

    if (type & F_OPEN_A && type & F_OPEN_W)
    {
        return (result_file_t){(file_t){0}, 0, 2, 0};
    }

    u64 access =
        (type & F_OPEN_R ? GENERIC_READ : 0)
        | (type & F_OPEN_W ? GENERIC_WRITE : 0)
        | (type & F_OPEN_A ? FILE_APPEND_DATA : 0);

    u64 creation =
        (type & F_OPEN_C ? OPEN_ALWAYS : 0)
        | (type & F_OPEN_D ? CREATE_ALWAYS : 0);

    if (type & F_OPEN_A)
    {
        creation = OPEN_ALWAYS;
        access &= ~GENERIC_WRITE;
    }

    //Actual file creation happens here
    HANDLE hh = CreateFileA(path, access, 0, NULL, creation, FILE_ATTRIBUTE_NORMAL,
                            NULL);
    if (hh == INVALID_HANDLE_VALUE)
    {
        return (result_file_t){(file_t){0}, 0, 1, GetLastError()};
    }

    return (result_file_t){(file_t){type, hh}, 1, 0, 0};
}
