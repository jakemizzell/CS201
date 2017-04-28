cmake_minimum_required(VERSION 3.6)
project(project3)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES dijkstra.c darray.h darray.c binomial.h binomial.c integer.h integer.c queue.c queue.h sll.c sll.h scanner.h scanner.c vertex.c vertex.h)
add_executable(djikstra ${SOURCE_FILES})