# minimal version
cmake_minimum_required(VERSION 3.24.0)

# GCC toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/CMake/arm_gcc_toolchain.cmake)

###################  CUSTOM  Options ##################

set(OpenOCD openocd)

# "Use start c"
set(USE_START_C ON)

message(STATUS "Use start c: ${USE_START_C}")

###################  CUSTOM Options ###################

# Project name, version and language
project(A36Plus VERSION 0.1.0 LANGUAGES C ASM)

# Compile type Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# Include all of the head need
include_directories(Core/Inc)
include_directories(Users/Inc)


include_directories(Libraries/GD32/)
include_directories(Libraries/printf/)
include_directories(Libraries/GD32/CMSIS)
include_directories(Libraries/GD32/CMSIS/GD/GD32F3x0/Include)
include_directories(Libraries/GD32/GD32F3x0_standard_peripheral/Include)

include_directories(Drivers/LCD)
include_directories(Drivers/BK1080)
include_directories(Drivers/BK4819)
include_directories(Drivers/Flash)
include_directories(Drivers/Key)


# Add definition
add_definitions(
    -DUSE_STDPERIPH_DRIVER
    -DGD32F3X0
    -DGD32F330
)

# Add all source files by recurse
file(GLOB_RECURSE FIRMWAR_SOURCE_DIR 
    Libraries/printf/*.c
    Libraries/GD32/GD32F3x0_standard_peripheral/*.c 
    Libraries/GD32/CMSIS/GD/GD32F3x0/Source/syscall.c  
    Libraries/GD32/CMSIS/GD/GD32F3x0/Source/system_gd32f3x0.c  
    # Libraries/GD32/CMSIS/GD/GD32F3x0/Source/GNU/*.s
)

if (USE_START_C)
    set(FIRMWAR_SOURCE_DIR "${FIRMWAR_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/Libraries/GD32/CMSIS/GD/GD32F3x0/Source/start.c")
else ()
    set(FIRMWAR_SOURCE_DIR "${FIRMWAR_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/Libraries/GD32/CMSIS/GD/GD32F3x0/Source/GNU/startup_gd32f3x0.s")
endif()

# message(STATUS "FIRMWAR_SOURCE_DIR: ${FIRMWAR_SOURCE_DIR}")

file(GLOB_RECURSE DRIVERS_SOURCE_DIR Drivers/*.c)

file(GLOB_RECURSE CORE_SOURCE_DIR Core/Src/*.c)

file(GLOB_RECURSE USER_SOURCE_DIR Users/Src/*.c)



# compile and link
add_executable(${PROJECT_NAME}.elf ${FIRMWAR_SOURCE_DIR} ${USER_SOURCE_DIR} ${DRIVERS_SOURCE_DIR} ${CORE_SOURCE_DIR})


# Execute custom command after compiling
add_custom_command(
    TARGET "${PROJECT_NAME}.elf"
    POST_BUILD
    # Build .hex and .bin files
    COMMAND arm-none-eabi-objcopy -Obinary "${PROJECT_NAME}.elf" "${PROJECT_NAME}.bin"
    COMMAND arm-none-eabi-objcopy -Oihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex"
    COMMENT "Building ${PROJECT_NAME}.bin and ${PROJECT_NAME}.hex"
    # Display sizes
    COMMAND arm-none-eabi-size --format=berkeley ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMENT "Invoking: Cross ARM GNU Print Size"
)


add_custom_target(flash
    COMMAND ${OpenOCD} -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f ${CMAKE_CURRENT_SOURCE_DIR}/gd32f33x.cfg -c "program ${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME}.bin verify reset exit 0x08000000"
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME}.bin
    COMMENT "Flashing ${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME}.bin"
    
)

