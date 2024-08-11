//
// Created by tobin on 2024-08-10.
//

#ifndef POSER_SPINLOCK_H
#define POSER_SPINLOCK_H

#include "../dialect.h"

typedef struct {
    atomic u8
    state;
} spinlock_t;

spinlock_t spinlock_create();

/*@formatter:off*/
inline u8 spinlock_islocked(spinlock_t *x);
/*@formatter:on */

u0 spinlock_lock(spinlock_t *x);

u0 spinlock_unlock(spinlock_t *x);

#endif //POSER_SPINLOCK_H
