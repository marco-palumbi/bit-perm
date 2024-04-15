cmake_minimum_required(VERSION 3.21)
project(rank_unrank C)

# help macro
macro(log var)
    message(STATUS "${var}: ${${var}}")
endmacro()

# Other not used flags: -fsanitize=address -Wformat -Wformat-security -Wall -Wextra

execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion
        OUTPUT_VARIABLE GCC_VERSION)


if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -funroll-loops")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -funroll-loops -fsanitize=address -Wformat=0 -Werror -Wno-unused-function -Wno-unused-result -Wno-strict-prototypes -Wunused-value -Wunused-variable -Wundef")#-Wcast-align
else()
    message(FATAL_ERROR "CMAKE_BUILD_TYPE not valid")
endif()


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
log(CMAKE_MODULE_PATH)
include(stm32f4discovery)

log(CMAKE_C_COMPILER)
log(CMAKE_C_FLAGS)

set(CMAKE_C_STANDARD 11)





set(MAIN_TARGET bit-perm)



if(NOT ("${toolchain}" STREQUAL "arm-none-eabi-libopencm3"))
    set(TEST_ITERATIONS 1000000)
else()
    set(TEST_ITERATIONS 1000)
endif()

# executable
add_custom_exe(${MAIN_TARGET} src/main.c)
target_sources(${MAIN_TARGET} PRIVATE )
target_compile_definitions(${MAIN_TARGET} PRIVATE N_ITERATIONS=${TEST_ITERATIONS})

