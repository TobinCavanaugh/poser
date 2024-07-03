//
// Created by tobin on 7/2/2024.
//

#ifndef POSER_XPLAT_H
#define POSER_XPLAT_H


#ifdef __GNUC__
#define COMPILER GCC
#elif __clang__
#define COMPILER CLANG
#elif __TINYC__
#define COMPILER TINYC
#elif _MSC_VER
#define COMPILER MSVC
#elif MINGW
#define COMPILER MINGW
#else
#define COMPILER UNKNOWN_COMPILER
#endif

#define GCC 0
#define CLANG 1
#define MSVC 2
#define MINGW 3
#define TINYC 4
#define UNKNOWN_COMPILER 255


#ifdef WIN64
#define OS WIN
#elif WIN32
#define OS WIN
#elif WINNT
#define OS WIN
#elif _LINUX
#elif UNIX
#define OS IX
#elif _MACOS
#define OS MAC
#elif _BSD
#define OS BSD
#elif _SOLARIS
#define OS SOLARIS
#endif

#define WIN 0
#define LINUX 1
#define UNIX 2
#define BSD 3
#define SOLARIS 4
#define SOLARIS 4

#endif //POSER_XPLAT_H
