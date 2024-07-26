cmake_minimum_required(VERSION 3.25)
project(poser C)

set(CMAKE_C_STANDARD 90)

enable_language(ASM)

# Set our entry point
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -e entry ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -e entry ")

# Disable stdlib
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -nostdlib ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib ")

# Set our INLINE macro. We do this here because CLion formatting hates the inline keyword so the only workaround is this
# roundabout method. At least it allows inlining to be optional though so (☞ﾟヮﾟ)☞
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -U INLINE -DINLINE=inline")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -U INLINE -DINLINE=inline")

#set(CMAKE_C_DIALECT "GNU90")

add_executable(${PROJECT_NAME}

        main.c

        # /io
        poser/io/put.c

        # /mem
        poser/mem/halloc.c
        poser/mem/mem_copy.c
        poser/mem/mem_move.c
        poser/mem/mem_set.c

        # /str
        poser/str/hstr.c
        poser/str/str.c
        poser/str/to_str.c
        poser/sys/sysinf.c

        poser/sys/sys_exit.c poser/sys/___chkstk_ms.c)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE kernel32)
endif ()
