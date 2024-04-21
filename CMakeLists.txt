cmake_minimum_required(VERSION 3.10)

project(
  cunit
  C
)

add_executable(main main.c cunit.c)
include_directories(.)
# set_property(TARGET CUnit PROPERTY C_STANDARD 23)

# Add libraries

add_library(cunit cunit.c cunit.h)

# Link libraries

    # target_link_libraries(MyExample PRIVATE MyLibExample)