//
// Created by tobin on 2024-08-10.
//
#include "../dialect.h"

#ifndef POSER_SPINLOCK_H
#define POSER_SPINLOCK_H

typedef struct {
    atomic u8
    state;
} spinlock_t;


/// Create a spinlock_t
/// \return The newly created spinlock object
spinlock_t spinlock_create();

/*@formatter:off*/
/// Check the condition of a spinlock
/// \param x : the pointer to the spinlock_t
/// \return the state of the spinlock. 1 if its locked, 0 if its unlocked
inline u8 spinlock_islocked(spinlock_t *x);
/*@formatter:on */


/// Lock the spinlock. This will deadlock if the spinlock is already locked.
/// \param x : The pointer to the spinlock_t
/// \param x : The pointer to the spinlock struct
u0 spinlock_lock(spinlock_t *x);

/// unlock the spinlock. this will never deadlock.
/// \param x : the pointer to the spinlock_t
u0 spinlock_unlock(spinlock_t *x);

#endif //POSER_SPINLOCK_H
