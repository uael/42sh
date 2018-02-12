cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(42sh C)
add_subdirectory(vendor/libft)
add_subdirectory(vendor/libps)
add_subdirectory(vendor/librl)

set(BUILD_SHARED_LIBS OFF)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(42sh_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(42sh_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(42sh_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

set(42sh_HDR ${42sh_INC_DIR}/ush.h src/bi/cd.c)
file(GLOB_RECURSE 42sh_HDRS ${42sh_HDRS} ${42sh_INC_DIR}/ush/*.h)
file(GLOB_RECURSE 42sh_SRCS ${42sh_SRCS} ${42sh_SRC_DIR}/*.c)
file(GLOB_RECURSE 42sh_SRCS ${42sh_SRCS} ${42sh_SRC_DIR}/*.h)

add_executable(42sh ${42sh_HDR} ${42sh_HDRS} ${42sh_SRCS})
set_property(TARGET 42sh PROPERTY C_STANDARD 90)
target_include_directories(42sh PUBLIC ${42sh_INC_DIR})
target_link_libraries(42sh PUBLIC debug ft debug rl debug ps)

target_compile_definitions(42sh
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
if (MSVC)
  target_compile_options(42sh
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(42sh
    PRIVATE -Wall -Werror -Wextra
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
