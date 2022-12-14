# STM32 Minimal CMake project for C/C++ projects
cmake_minimum_required(VERSION 3.12)
###############################################################################
# Set project name and source code folder location
project(stm32-nucleo-f446re)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Project)
set(PROJECT_SRC ${PROJECT_DIR}/Src)
set(PROJECT_INC ${PROJECT_DIR}/Include)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(DUMP_ASM "Create full assembly of final executable" OFF)

# Set microcontroller information
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F446xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

set(STARTUP_SCRIPT ${PROJECT_DIR}/Startup/startup_stm32f446retx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F446RETX_FLASH.ld)

###############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

###############################################################################
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_SRC}/*.cpp
    ${PROJECT_SRC}/*.c
)

add_subdirectory(Core stm32f446xx_core)
add_subdirectory(Drivers stm32f446xx_drivers)

add_executable(${EXECUTABLE}
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT}
)

target_link_libraries(${EXECUTABLE} stm32f446xx_core)
target_link_libraries(${EXECUTABLE} stm32f446xx_drivers)

target_compile_definitions(${EXECUTABLE} PRIVATE
    # $<$<CONFIG:Debug>:DEBUG>
    ${MCU_MODEL}
)

###############################################################################
target_compile_options(${EXECUTABLE} PRIVATE
${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wdouble-promotion
    -Wformat=2 -Wformat-truncation
    -Wundef
    -fno-common
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wconversion # STM libraries!
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>
)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage
)

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.bin)

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXECUTABLE}.s)
endif()