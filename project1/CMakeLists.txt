cmake_minimum_required(VERSION 3.6)
project(project1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES scanner.c integer.c sll.c dll.c queue.c stack.c real.c string.c comparator.c sqsort.c reader.c)
add_executable(sqsort-v ${SOURCE_FILES})

set(SOURCE_FILES scanner.c integer.c sll.c dll.c queue.c stack.c real.c string.c comparator.c sqsort.c reader.c)
add_executable(sqsort-d ${SOURCE_FILES})

set(SOURCE_FILES scanner.c integer.c sll.c dll.c queue.c stack.c real.c string.c comparator.c sqsort.c reader.c)
add_executable(sqsort-r ${SOURCE_FILES})

set(SOURCE_FILES scanner.c integer.c sll.c dll.c queue.c stack.c real.c string.c comparator.c sqsort.c reader.c)
add_executable(sqsort-s ${SOURCE_FILES})

set(SOURCE_FILES string.c test-string.c)
add_executable(test-string ${SOURCE_FILES})

set(SOURCE_FILES real.c test-real.c)
add_executable(test-real ${SOURCE_FILES})