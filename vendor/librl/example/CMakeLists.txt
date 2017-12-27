macro(add_example NAME)
  add_executable(${NAME} ${ARGN})
  set_property(TARGET ${NAME} PROPERTY C_STANDARD 90)
  target_link_libraries(${NAME} rl)

  target_compile_definitions(${NAME}
    PRIVATE $<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:NDEBUG>
    PRIVATE API_COMPILE)
  if (MSVC)
    target_compile_options(${NAME}
      PRIVATE /MT$<$<CONFIG:Debug>:d> /Oy /W3
      PRIVATE /D_CRT_SECURE_NO_WARNINGS /Dinline=__inline
      PRIVATE /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
  else ()
    target_compile_options(${NAME}
      PRIVATE -Wall -Werror -Wextra -fomit-frame-pointer -ansi
      PRIVATE -Wno-missing-field-initializers -Wno-missing-braces
      PRIVATE -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
  endif ()
endmacro()

add_example(cli cli.c)
