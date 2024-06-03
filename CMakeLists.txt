# minimal version
cmake_minimum_required(VERSION 3.24.0)

# GCC toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CMake/arm_cc_toolchain.cmake)

# Project name, version and language
project(A36Plus VERSION 0.1.0 LANGUAGES C ASM)

# Compile type Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# Include all of the head need
include_directories(Users/Inc)
include_directories(Libraries/GD32/)
include_directories(Libraries/GD32/CMSIS)
include_directories(Libraries/GD32/CMSIS/GD/GD32F3x0/Include)
include_directories(Libraries/GD32/GD32F3x0_standard_peripheral/include)

include_directories(Drivers/LCD)
include_directories(Drivers/BK1080)
include_directories(Drivers/BK4819)
include_directories(Drivers/Flash)

include_directories(Hardware/Inc)

# Add definition
add_definitions(
    -DUSE_STDPERIPH_DRIVER
    -DGD32F3X0
    -DGD32F330
)

# Add all source files by recurse
file(GLOB_RECURSE FIRMWAR_SOURCE_DIR 
    Libraries/GD32/GD32F3x0_standard_peripheral/*.c 
    Libraries/GD32/CMSIS/GD/GD32F3x0/Source/*.c  
    Libraries/GD32/CMSIS/GD/GD32F3x0/Source/GNU/*.s
)

# message(STATUS "FIRMWAR_SOURCE_DIR: ${FIRMWAR_SOURCE_DIR}")

file(GLOB_RECURSE DRIVERS_SOURCE_DIR Drivers/*.c)

file(GLOB_RECURSE HARDWARE_SOURCE_DIR Hardware/Src/*.c)

file(GLOB_RECURSE USER_SOURCE_DIR Users/Src/*.c)



# compile and link
add_executable(A36Plus ${FIRMWAR_SOURCE_DIR} ${USER_SOURCE_DIR} ${DRIVERS_SOURCE_DIR} ${HARDWARE_SOURCE_DIR})


# Execute custom command after compiling
add_custom_command(
    TARGET "${PROJECT_NAME}"
    POST_BUILD
    # Build .hex and .bin files
    COMMAND arm-none-eabi-objcopy -Obinary "${PROJECT_NAME}.elf" "${PROJECT_NAME}.bin"
    COMMAND arm-none-eabi-objcopy -Oihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex"
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"
    # Display sizes
    COMMAND arm-none-eabi-size --format=berkeley ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Invoking: Cross ARM GNU Print Size"
)

