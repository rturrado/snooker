cmake_minimum_required(VERSION 3.22)

project("snooker"
    VERSION 1.0
    DESCRIPTION "An OpenGL implementation of the snooker game."
    HOMEPAGE_URL https://github.com/rturrado/snooker.git
    LANGUAGES C CXX
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
