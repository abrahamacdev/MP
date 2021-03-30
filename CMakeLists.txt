cmake_minimum_required(VERSION 3.17)
project(MP C)

set(CMAKE_C_STANDARD 99)

add_executable(MP main.c equipos/equipos.c equipos/equipos.h futbolistas/futbolistas.c futbolistas/futbolistas.h tests/tests_equipos.c tests/tests_equipos.h tests/tests_futbolistas.c tests/tests_futbolistas.h cronista.c cronista.h estructuras.h)