cmake_minimum_required(VERSION 3.27)
project(mango C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -s")

add_executable(mango
        src/main.c
        src/color.c
        src/console.c
        src/mango.c
)

target_link_libraries(mango m)