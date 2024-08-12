//
// Created by tobin on 2024-08-10.
//

#include "spinlock.h"

spinlock_t spinlock_create() {
    spinlock_t x = (spinlock_t) {0};
    x.state = 0;
    return x;
}


/*@formatter:off*/
inline u8 spinlock_islocked(spinlock_t *x) {
return !!x->state;
}
/*@formatter:on */

u0 spinlock_lock(spinlock_t *x) {
    while (spinlock_islocked(x)) {/*wait*/}
    x->state = 1;
}

u0 spinlock_unlock(spinlock_t *x) {
    x->state = 0;
}
