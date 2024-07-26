//
// Created by tobin on 7/2/2024.
//

#ifndef POSER_SYS_PLAT_H
#define POSER_SYS_PLAT_H


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


#define OS_WIN 1
#define OS_LINUX 2
#define OS_MACOS 3
#define OS_SOLARIS 4

#ifdef _WIN32
#define SYS_OS OS_WIN
#elif defined(_WIN64)
#define SYS_OS OS_WIN
#elif defined(__linux__)
#define SYS_OS OS_LINUX
#elif defined(__APPLE__ )
#define SYS_OS OS_MACOS
#elif defined(__sun)
#define SYS_OS OS_SOLARIS
#endif


#endif //POSER_SYS_PLAT_H
