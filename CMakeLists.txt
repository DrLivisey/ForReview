cmake_minimum_required(VERSION 3.16)

# Настройки микроконтроллера.
set(STM32_CHIP STM32L433C8T6)

set(STM32_CUBE_L4_PATH ${CMAKE_CURRENT_SOURCE_DIR}/STM32Cube_FW_L4_V1.18.0)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)


# Настройки проекта.
project(aqbm1000ll C ASM)

if(NOT CMAKE_BUILD_TYPE)
  #set(CMAKE_BUILD_TYPE Release)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Настройки подключаемых модулей.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(CMSIS COMPONENTS ${STM32_CHIP} REQUIRED)
find_package(HAL COMPONENTS ${STM32_CHIP} LL_GPIO LL_RCC LL_EXTI LL_PWR LL_USART LL_UTILS REQUIRED)

# Настройки параметров сборки проекта.
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
  ${SOURCE_DIR}/gpio.c
  ${SOURCE_DIR}/main.c
  ${SOURCE_DIR}/usart.c
)


set(STM32_LINKER_SCRIPT ${CMSIS_LINKER_SCRIPT})

include_directories(${SOURCE_DIR} ${CMSIS_INCLUDE_DIRS} ${INC_DIR})

add_definitions(-DSTM32L433xx)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DUSE_FULL_ASSERT)
endif()

add_definitions(-DUSE_FULL_LL_DRIVER)

add_executable(${PROJECT_NAME} ${STM32LL_SOURCES} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    HAL::STM32::L4::LL_GPIO 
    HAL::STM32::L4::LL_RCC 
    HAL::STM32::L4::LL_EXTI 
    HAL::STM32::L4::LL_PWR 
    HAL::STM32::L4::LL_USART 
    HAL::STM32::L4::LL_UTILS 
    CMSIS::STM32::L433xx
    STM32::NoSys
    
)
stm32_print_size_of_target(${PROJECT_NAME})

stm32_generate_binary_file(${PROJECT_NAME})
stm32_generate_hex_file(${PROJECT_NAME})

#stm32_set_target_properties(${PROJECT_NAME})
#stm32_set_hse_value(${PROJECT_NAME} 12000000)

#set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Werror -Wmissing-declarations")

#stm32_add_hex_bin_targets(${PROJECT_NAME})
#stm32_add_dump_target(${PROJECT_NAME})

#stm32_print_size_of_targets(${PROJECT_NAME})
