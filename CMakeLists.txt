cmake_minimum_required(VERSION 3.10)

project(
  cunit
  C
)
add_compile_options(-std=c23)

add_executable(main main.c cunit.c)
include_directories(.)

# Add libraries

add_library(cunit cunit.c cunit.h)
# Link libraries

  target_link_libraries(cunit)