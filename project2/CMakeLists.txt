cmake_minimum_required(VERSION 3.6)
project(project2)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES bst.c bstrees.c vbst.h vbst.c rbt.h rbt.c scanner.c scanner.h string.c string.h comparator.c comparator.h real.c real.h integer.c integer.h sll.c sll.h queue.c queue.h read.h read.c)
add_executable(bstrees-b ${SOURCE_FILES})
add_executable(bstrees-v ${SOURCE_FILES})
add_executable(bstrees-r ${SOURCE_FILES})
