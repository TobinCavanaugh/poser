//
// Created by tobin on 2024-10-01.
//

#ifndef WRITE_H
#define WRITE_H

#include "../dialect.h"
#include "../io/put.h"

typedef enum
{
    F_OPEN_W = /*----*/ 0b00001, /*Write*/
    F_OPEN_R = /*----*/ 0b00010, /*Read*/
    F_OPEN_C = /*----*/ 0b00100, /*Create/preserve contents*/
    F_OPEN_D = /*----*/ 0b01000, /*Create/destroy contents*/
    F_OPEN_A = /*----*/ 0b10000, /*Open for appending*/
    F_OPEN_RW = /*---*/ 0b00011, /*Read/Write*/
    F_OPEN_RWC = /*--*/ 0b00111, /*Create/Read/Write/preserve contents*/
    F_OPEN_RWD = /*--*/ 0b01011, /*Create/Read/Write/destroy contents*/
} F_OPEN_TYPES;


typedef struct
{
    F_OPEN_TYPES type;
    void* handle;
} file_t;

/* FAILURE CODES:
 * 0: NONE
 * 1: PLATFORM SPECIFIC ERROR, see systemFailureCode
 * 2: INVALID F_OPEN_TYPES
 *      - F_OPEN_W | F_OPEN_A : Writing and appending cannot be done in the
 *      same file open call
 *      - F_OPEN_C | F_OPEN_D : These are mutually exclusive, the file creation
 *      can either keep the file contents or they can be destroyed
 */

typedef struct
{
    file_t value; /*The file_t type*/
    u8 success; /*1 for success, 0 for failure*/
    u8 failureCode; /*Poser error code*/
    u8 systemFailureCode; /*Platform specific error code*/
} result_file_t;

result_file_t file_open(char* path, F_OPEN_TYPES type);

#endif //WRITE_H
