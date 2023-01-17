set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})


# Sources
set(lib_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/Ball.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PlayingSurface.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Pocket.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Trajectory.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Utility.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Vertex.cpp"
)
set(app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/Snooker.cpp"
)
list(APPEND app_sources ${lib_sources})


# Main library
add_library(lib_${PROJECT_NAME} ${lib_sources})
target_include_directories(lib_${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(lib_${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}
)
target_compile_features(lib_${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(lib_${PROJECT_NAME} PUBLIC
    ${CONAN_LIBS}
)


# Main executable
add_executable(${PROJECT_NAME} ${app_sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE lib_${PROJECT_NAME})


# Target compile options
if(MSVC)
    set(msvc_compile_options
        /W3 /WX /w34996
        /D_CONSOLE /DCONSOLE
        /D_UNICODE /DUNICODE
        /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /MP /sdl /utf-8 /Zc:inline
    )
    target_compile_options(lib_${PROJECT_NAME} PRIVATE ${msvc_compile_options})
    target_compile_options(${PROJECT_NAME} PRIVATE ${msvc_compile_options})
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(unixlike_compile_options
        -pedantic-errors -Werror -Wall -Wextra
        -Wl,-z,defs
        -Wno-deprecated
        # -Wconversion -Wsign-conversion -Wno-sign-conversion  # do not sort flags; order matters
    )
    target_compile_options(lib_${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
    target_compile_options(${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
endif()
