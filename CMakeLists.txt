cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(minishell C)
add_subdirectory(libft)

set(BUILD_SHARED_LIBS OFF)

set(minishell_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(minishell_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(minishell_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

set(minishell_HDR ${minishell_INC_DIR}/minishell.h)
file(GLOB_RECURSE minishell_HDRS ${minishell_HDRS} ${minishell_INC_DIR}/ls/*.h)
file(GLOB_RECURSE minishell_SRCS ${minishell_SRCS} ${minishell_SRC_DIR}/*.c)

add_executable(minishell ${minishell_HDR} ${minishell_HDRS} ${minishell_SRCS})
set_property(TARGET minishell PROPERTY C_STANDARD 90)
target_include_directories(minishell PUBLIC ${minishell_INC_DIR})
target_link_libraries(minishell PUBLIC ft)

target_compile_definitions(minishell
    PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
    target_compile_options(minishell
        PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
        PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
        PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
    target_compile_options(minishell
        PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
        PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
        PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
