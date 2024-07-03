cmake_minimum_required(VERSION 3.25)
project(poser C)

set(CMAKE_C_STANDARD 90)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -e entry -nostdlib ")

# Set our INLINE macro. We do this here because CLion formatting hates the inline keyword so the only workaround is this
# roundabout method. At least it allows inlining to be optional though so (☞ﾟヮﾟ)☞
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -U INLINE -DINLINE=inline")

set(CMAKE_C_DIALECT "GNU90")

add_executable(poser main.c poser/io/put.c poser/str/str.c poser/mem/mem_copy.c)
