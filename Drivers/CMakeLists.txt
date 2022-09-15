cmake_minimum_required(VERSION 3.12)

set(LIBRARY_NAME stm32f446xx_drivers)
set(LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/Src)
set(LIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/Include)

set(PROJECT_INCLUDES
    ${LIB_INC}
)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${LIB_SRC}/*.cpp
    ${LIB_SRC}/*.c
)

add_library(${LIBRARY_NAME} STATIC
    ${PROJECT_SOURCES}
)

target_compile_options(${LIBRARY_NAME} PRIVATE 
    ${CPU_PARAMETERS}
    -Wall
)

target_include_directories(${LIBRARY_NAME} PUBLIC 
    # $<INSTALL_INTERFACE:${PROJECT_INCLUDES}>
    # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_INCLUDES}>
    ${PROJECT_INCLUDES}
)

target_link_libraries(${LIBRARY_NAME} stm32f446xx_core)



