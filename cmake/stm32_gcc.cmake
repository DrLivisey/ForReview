if(${CMAKE_VERSION} VERSION_LESS "3.16.0") 
    message(WARNING "Current CMake version is ${CMAKE_VERSION}. stm32-cmake requires CMake 3.16 or greater")

endif()

set(CMAKE_CROSSCOMPILING "true")
#set(STM32_TARGET_TRIPLET "/usr/gcc-arm-none-eabi-10.3-2021.07/bin/")


#cmake -DCMAKE_TOOLCHAIN_FILE=cmake/stm32_gcc.cmake .

get_filename_component(STM32_CMAKE_DIR ${CMAKE_CURRENT_LIST_FILE} DIRECTORY)
list(APPEND CMAKE_MODULE_PATH ${STM32_CMAKE_DIR})




add_compile_options(
    -mcpu=cortex-m0
)

include(stm32/common)
include(stm32/devices)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

find_program(CMAKE_C_COMPILER NAMES ${STM32_TARGET_TRIPLET}-gcc HINTS ${TOOLCHAIN_BIN_PATH})
find_program(CMAKE_CXX_COMPILER NAMES ${STM32_TARGET_TRIPLET}-g++ HINTS ${TOOLCHAIN_BIN_PATH})
find_program(CMAKE_ASM_COMPILER NAMES ${STM32_TARGET_TRIPLET}-gcc HINTS ${TOOLCHAIN_BIN_PATH})

set(CMAKE_EXECUTABLE_SUFFIX_C   .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)
set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)

#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# This should be safe to set for a bare-metal cross-compiler
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
