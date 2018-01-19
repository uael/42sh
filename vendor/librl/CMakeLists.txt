cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(librl C)
get_directory_property(librl_PARENT PARENT_DIRECTORY)

set(BUILD_SHARED_LIBS OFF)

set(librl_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(librl_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(librl_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

option(COVERAGE "Turn on COVERAGE support" OFF)
if (COVERAGE AND NOT MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif ()

if (NOT librl_PARENT AND EXISTS ${librl_TEST_DIR})
  enable_testing()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
  set(librl_ENABLE_TEST ON)
else ()
  set(librl_ENABLE_TEST OFF)
endif ()

set(librl_HDR ${librl_INC_DIR}/librl.h src/signal.c src/signal.h)
file(GLOB_RECURSE librl_HDRS ${librl_HDRS}
  ${librl_INC_DIR}/librl/*.h)
file(GLOB_RECURSE librl_SRCS ${librl_SRCS}
  ${librl_SRC_DIR}/*.c)
file(GLOB_RECURSE librl_SRCS ${librl_SRCS}
  ${librl_SRC_DIR}/*.h)

add_library(rl ${librl_HDR} ${librl_HDRS} ${librl_SRCS})
set_property(TARGET rl PROPERTY C_STANDARD 90)
target_include_directories(rl PUBLIC ${librl_INC_DIR})
target_compile_definitions(rl PRIVATE U_COMPILE)
target_link_libraries(rl ft)

target_compile_definitions(rl
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
  PRIVATE API_COMPILE)
if (MSVC)
  target_compile_options(rl
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(rl
    PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
    PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()
