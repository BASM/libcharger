cmake_minimum_required (VERSION 2.8)
project (libir)
include_directories("include")

#SET(CMAKE_C_COMPILER avr-gcc)
#SET(CMAKE_CXX_COMPILER avr-gcc)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb3 ")

#TARGET_LINK_LIBRARIES(main m)

add_library(charger STATIC src/charger.c)

add_executable(main test/main.c test/getch.c)
target_link_libraries(main charger m)

