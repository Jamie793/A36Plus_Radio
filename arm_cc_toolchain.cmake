
set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_SYSTEM_PROCESSOR ARM)

# set(CMAKE_EXE_LINKER_FLAGS_INIT "-specs=nosys.specs")

set(TOOLCHAIN_PREFIX arm-none-eabi-)  

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)

set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)

set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}ld)

set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

set(CMAKE_AR ${TOOLCHAIN_PREFIX}gcc-ar)

set(CMAKE_NM ${TOOLCHAIN_PREFIX}nm)

set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcpy)

set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)

set(CMAKE_STRIP ${TOOLCHAIN_PREFIX}strip)

set(CMAKE_RANLIB ${TOOLCHAIN_PREFIX}ranlib)

set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)




# set(MCU "-mcpu=cortex-m4 -mthumb")

set(CMAKE_C_FLAGS  " -c --cpu Cortex-M4.fp -D__MICROLIB -g -O0 --apcs=interwork --split_sections " CACHE INTERNAL "C Compiler options")

set(CMAKE_ASM_FLAGS "--cpu Cortex-M4.fp -g --apcs=interwork" CACHE INTERNAL "ASM Compiler options")

set(CMAKE_EXE_LINKER_FLAGS_INIT "--cpu Cortex-M4.fp --library_type=microlib --strict --summary_stderr --info summarysizes --map ")

# add_compile_options(
#     -c 
#     --cpu Cortex-M4.fp 
#     -D__MICROLIB 
#     -g 
#     -O0 
#     --apcs=interwork 
#     --split_sections 
# )


add_link_options(
    --cpu Cortex-M4.fp *.o 
    --library_type=microlib --strict --scatter ".\output\Project.sct" 
    --summary_stderr --info summarysizes --map --xref --callgraph --symbols 
    --info sizes --info totals --info unused --info veneers 
     --list ".\Project.map" 
    -o .\output\Project.axf 
    
)
message(STATUS "arm toolchain is used")