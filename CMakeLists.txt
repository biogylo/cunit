cmake_minimum_required(VERSION 3.10)

project(
  CUnit
  C
)

add_executable(main main.c)
include_directories(.)
add_library(cunit cunit.c cunit.h)
# set_property(TARGET CUnit PROPERTY C_STANDARD 23)

# Add libraries

# add_library(cunit cunit.c cunit.h)

# Link libraries

    # target_link_libraries(MyExample PRIVATE MyLibExample)