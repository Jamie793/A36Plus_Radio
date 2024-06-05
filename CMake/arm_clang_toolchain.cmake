
cmake_minimum_required(VERSION 3.17)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Cortex-M4)


set(CMAKE_C_COMPILER armclang)
set(CMAKE_CXX_COMPILER armclang)
set(CMAKE_ASM_COMPILER armasm)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)


set(CMAKE_C_LINK_EXECUTABLE armlink)
set(CMAKE_CXX_LINK_EXECUTABLE armlink)
set(CMAKE_ASM_LINK_EXECUTABLE armlink)


set(CMAKE_C_FLAGS_INIT "\
    -xc \
    -std=c99 \
    --target=arm-arm-none-eabi \
    -mcpu=cortex-m4 \
    -mfpu=fpv4-sp-d16 \
    -mfloat-abi=hard \
    -c \
    -fno-rtti \
    -funsigned-char \
    -fshort-enums \
    -fshort-wchar \
    -gdwarf-3 \
    -Oz \
    -ffunction-sections \
    -Wno-packed \
    -Wno-missing-variable-declarations \
    -Wno-missing-prototypes \
    -Wno-missing-noreturn \
    -Wno-sign-conversion \
    -Wno-nonportable-include-path \
    -Wno-reserved-id-macro \
    -Wno-unused-macros \
    -Wno-documentation-unknown-command \
    -Wno-documentation \
    -Wno-license-management \
    -Wno-parentheses-equality \
" CACHE INTERNAL "C Flags")


set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT} CACHE STRING "CXX Flags")


set(CMAKE_ASM_FLAGS_INIT "\
--cpu Cortex-M4.fp \
-g\
" CACHE INTERNAL "ASM Flags")


# if (NOT SECTIONS_SCRIPT_PATH)
# message(FATAL_ERROR "You not set SECTIONS_SCRIPT_PATH!")
# endif ()


set(CMAKE_EXE_LINKER_FLAGS_INIT "\
    --cpu=Cortex-M4.fp \
    --strict \
    --summary_stderr \
    --info summarysizes \
    --load_addr_map_info \
    --callgraph \
    --symbols \
    --info sizes \
    --info totals \
    --info unused \
    --info veneers \
" CACHE STRING "Link Flags")

