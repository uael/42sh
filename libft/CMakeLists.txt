cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(libft C)
get_directory_property(libft_PARENT PARENT_DIRECTORY)

set(BUILD_SHARED_LIBS OFF)

set(libft_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(libft_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(libft_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

option(COVERAGE "Turn on COVERAGE support" OFF)
if (COVERAGE AND NOT MSVC)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif ()

if (NOT libft_PARENT AND EXISTS ${libft_TEST_DIR})
  enable_testing()
  add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
  set(libft_ENABLE_TEST ON)
else ()
  set(libft_ENABLE_TEST OFF)
endif ()

set(libft_HDR ${libft_INC_DIR}/libft.h)
file(GLOB_RECURSE libft_HDRS ${libft_HDRS}
  ${libft_INC_DIR}/libft/*.h)
file(GLOB_RECURSE libft_SRCS ${libft_SRCS}
  ${libft_SRC_DIR}/*.c)
file(GLOB_RECURSE libft_SRCS ${libft_SRCS}
  ${libft_SRC_DIR}/*.h)

add_library(ft ${libft_HDR} ${libft_HDRS} ${libft_SRCS})
set_property(TARGET ft PROPERTY C_STANDARD 90)
target_include_directories(ft PUBLIC ${libft_INC_DIR})
target_compile_definitions(ft PRIVATE U_COMPILE)
target_link_libraries(ft mlx)

target_compile_definitions(ft
  PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
  PRIVATE API_COMPILE)
if (MSVC)
  target_compile_options(ft
    PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
    PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
    PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(ft
    PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
    PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
    PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

if (libft_ENABLE_TEST)
  file(GLOB libft_TEST_SRCS ${libft_TEST_SRCS}
    ${libft_TEST_DIR}/*.c)
  foreach (libft_TEST_SRC ${libft_TEST_SRCS})
    get_filename_component(libft_TEST_NAME ${libft_TEST_SRC} NAME_WE)
    set(test test_libft_${libft_TEST_NAME})
    add_executable(${test} ${libft_TEST_SRC})
    set_property(TARGET ${test}
      PROPERTY C_STANDARD 90)
    add_dependencies(${test} ft)
    add_dependencies(check ${test})
    target_include_directories(${test} PUBLIC
      ${libft_TEST_DIR})
    target_link_libraries(${test} ft)
    target_compile_definitions(${test}
      PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>)
    add_test(libft_${libft_TEST_NAME} ${test}
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
    if (MSVC)
      target_compile_options(${test}
        PRIVATE /MTd /Oy /W3
        PRIVATE /D_CRT_SECURE_NO_WARNINGS
        PRIVATE /Od)
    else ()
      target_compile_options(${test}
        PRIVATE -fomit-frame-pointer -ansi
        PRIVATE -O0 -g3)
    endif ()
  endforeach ()
endif ()
