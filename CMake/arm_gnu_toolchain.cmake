
cmake_minimum_required(VERSION 3.17)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Cortex-M4)


set(CMAKE_C_COMPILER armclang)
set(CMAKE_CXX_COMPILER armclang)
set(CMAKE_ASM_COMPILER armclang)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)


set(CMAKE_C_LINK_EXECUTABLE armlink)
set(CMAKE_CXX_LINK_EXECUTABLE armlink)
set(CMAKE_ASM_LINK_EXECUTABLE armlink)



# set(COMPILE_RULE_FLAG "-mcpu=${CMAKE_SYSTEM_PROCESSOR} ${FPU_FLAG}")


set(CMAKE_C_FLAGS_INIT "\
    -c\
" CACHE INTERNAL "global")


# set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT} CACHE STRING "global")


set(CMAKE_ASM_FLAGS_INIT "\
--cpu Cortex-M4.fp\
-g\
" CACHE INTERNAL "global")


# if (NOT SECTIONS_SCRIPT_PATH)
# message(FATAL_ERROR "You not set SECTIONS_SCRIPT_PATH!")
# endif ()


# set(CMAKE_EXE_LINKER_FLAGS_INIT "\
#     --cpu=Cortex-M4.fp\
# " CACHE STRING "global")
