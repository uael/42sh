cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(21sh C)
add_subdirectory(libft)

set(BUILD_SHARED_LIBS OFF)

set(21sh_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(21sh_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(21sh_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

set(21sh_HDR ${21sh_INC_DIR}/msh.h)
file(GLOB_RECURSE 21sh_HDRS ${21sh_HDRS} ${21sh_INC_DIR}/msh/*.h)
file(GLOB_RECURSE 21sh_SRCS ${21sh_SRCS} ${21sh_SRC_DIR}/*.c)
file(GLOB_RECURSE 21sh_SRCS ${21sh_SRCS} ${21sh_SRC_DIR}/*.h)

add_executable(21sh ${21sh_HDR} ${21sh_HDRS} ${21sh_SRCS})
set_property(TARGET 21sh PROPERTY C_STANDARD 90)
target_include_directories(21sh PUBLIC ${21sh_INC_DIR})
target_link_libraries(21sh PUBLIC ft ncurses)
target_compile_definitions(ft PUBLIC FT_CLI=21sh)

target_compile_definitions(21sh
    PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
    target_compile_options(21sh
        PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
        PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
        PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
    target_compile_options(21sh
        PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
        PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
        PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

add_executable(main src/main.c)
set_property(TARGET main PROPERTY C_STANDARD 90)
target_include_directories(main PUBLIC ${21sh_INC_DIR})
target_link_libraries(main PUBLIC ft ncurses)
target_compile_definitions(ft PUBLIC FT_CLI=21sh)

target_compile_definitions(main
        PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
    target_compile_options(main
            PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
            PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
            PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
    target_compile_options(main
            PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
            PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
            PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
