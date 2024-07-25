//
// Created by tobin on 2024-07-25.
//

#ifndef POSER_SALLOC_H
#define POSER_SALLOC_H

//#define salloc(size) ({u8 tmp[size]; tmp;})
//TODO Needs custom salloc implementation
#define salloc(size) __builtin_alloca(size);

#endif //POSER_SALLOC_H
