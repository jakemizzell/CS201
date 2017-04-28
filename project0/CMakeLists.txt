cmake_minimum_required(VERSION 3.6)
project(project0)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES integer.c sll.c sll.h test-sll.c)
add_executable(test-sll ${SOURCE_FILES})

set(SOURCE_FILES integer.c dll.c dll.h test-dll.c)
add_executable(test-dll ${SOURCE_FILES})

set(SOURCE_FILES integer.c dll.h dll.c stack.c stack.h test-s.c)
add_executable(test-s ${SOURCE_FILES})

set(SOURCE_FILES integer.c sll.h sll.c queue.c queue.h test-q.c)
add_executable(test-q ${SOURCE_FILES})