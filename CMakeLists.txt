cmake_minimum_required(VERSION 3.17)
project(MP C)

set(CMAKE_C_STANDARD 99)

add_executable(MP main.c cronista/equipos/equipos.c cronista/equipos/equipos.h cronista/futbolistas/futbolistas.c cronista/futbolistas/futbolistas.h cronista/tests/tests_equipos.c cronista/tests/tests_equipos.h cronista/tests/tests_futbolistas.c cronista/tests/tests_futbolistas.h cronista/cronista.c cronista/cronista.h cronista/estructuras_cronista.h)