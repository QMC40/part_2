cmake_minimum_required(VERSION 3.21)
project(part_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(../project/exec)

add_executable(part_2
        definitions.h
        lex.yy.c
        part2.c)
