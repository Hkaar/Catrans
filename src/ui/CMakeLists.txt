# This is for a shared lib
# add_definitions(-DUI_EXPORTS)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

# This is for a shared lib
# add_library(ui_lib SHARED
#     ${SOURCES}
# )

add_library(ui_lib STATIC
    ${SOURCES}
)

target_include_directories(ui_lib 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include
)

set_target_properties(ui_lib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "ui_lib"
    DEBUG_POSTFIX "d"
)

add_library(core_lib STATIC
    ${CMAKE_SOURCE_DIR}/src/core.c
    ${CMAKE_SOURCE_DIR}/src/helpers.c
    ${CMAKE_SOURCE_DIR}/src/catrans.c
)

target_include_directories(core_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(ui_lib PRIVATE core_lib)

# Specific flag for windows for a shared library
# if(WIN32)
#     target_compile_definitions(ui_lib
#         PRIVATE "UI_EXPORTS"
#         INTERFACE "UI_IMPORTS"
#     )
# endif()

install(TARGETS ui_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

