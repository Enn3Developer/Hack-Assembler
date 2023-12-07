cmake_minimum_required(VERSION 3.26)
project(progetto5 C)

set(CMAKE_C_STANDARD 11)

add_executable(progetto5 main.c
        file.h
        file.c
        string.c
        string.h
        preproccesor.c
        preproccesor.h
        variables.c
        variables.h)
