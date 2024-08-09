//
// Created by tobin on 2024-08-08.
//

#ifndef POSER_MUTEX_H
#define POSER_MUTEX_H

#include "../comp/bint.h"

typedef struct{
    u8 state;
} spinlock_t;

spinlock_t thrd_create_sl();


#endif //POSER_MUTEX_H
