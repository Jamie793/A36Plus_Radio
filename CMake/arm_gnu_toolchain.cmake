#设置CMake最低支持版本
cmake_minimum_required(VERSION 3.17)

#交叉编译：设置目标机器类型
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR Cortex-M4)

#设置编译器
set(CMAKE_C_COMPILER armclang)
set(CMAKE_CXX_COMPILER armclang)
set(CMAKE_ASM_COMPILER armclang)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

#设置链接器
set(CMAKE_C_LINK_EXECUTABLE armlink)
set(CMAKE_CXX_LINK_EXECUTABLE armlink)
set(CMAKE_ASM_LINK_EXECUTABLE armlink)


#设置通用编译参数
# set(COMPILE_RULE_FLAG "-mcpu=${CMAKE_SYSTEM_PROCESSOR} ${FPU_FLAG}")

#设置C编译器选项
set(CMAKE_C_FLAGS_INIT "\
    -c\
" CACHE INTERNAL "global")

#设置C++编译器选项
# set(CMAKE_CXX_FLAGS_INIT ${CMAKE_C_FLAGS_INIT} CACHE STRING "global")

#设置ASM编译器选项
set(CMAKE_ASM_FLAGS_INIT "\
--cpu Cortex-M4.fp\
-g\
" CACHE INTERNAL "global")

#判断链接脚本是否存在
# if (NOT SECTIONS_SCRIPT_PATH)
# message(FATAL_ERROR "You not set SECTIONS_SCRIPT_PATH!")
# endif ()

#设置链接选项
# set(CMAKE_EXE_LINKER_FLAGS_INIT "\
#     --cpu=Cortex-M4.fp\
# " CACHE STRING "global")
