//
// Created by tobin on 7/2/2024.
//

#ifndef POSER_RARE_H
#define POSER_RARE_H

#ifdef __builtin_expect
#define rare(condition) __builtin_expect(condition, 0)
#else
#define rare(condition) condition
#endif

#ifdef __builtin_expect
#define common(condition) __builtin_expect(condition, 1)
#else
#define common(condition) condition
#endif

#endif //POSER_RARE_H
