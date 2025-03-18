cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

project(catrans VERSION 1.0.0 LANGUAGES C)

add_executable(${PROJECT_NAME}
    src/main.c
    src/core.c
    src/helpers.c
    src/catrans.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/include
)

add_subdirectory(src/ui)

target_link_libraries(${PROJECT_NAME} ui_lib)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<C_COMPILER_ID:GNU>:-Wall -Wextra>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)
