cmake_minimum_required(VERSION 3.12)
project(PSE_SystemC_watertank)

set(CMAKE_CXX_STANDARD 14)
set(SYSTEMC_HOME $ENV{SYSTEMC_HOME})
if (NOT SYSTEMC_HOME)
    set(SYSTEMC_HOME "/usr/local/systemc-2.3.3/")
endif ()
message("Env variable SYSTEMC_HOME = " ${SYSTEMC_HOME})
set(SCAMS_HOME $ENV{SCAMS_HOME})
if (NOT SCAMS_HOME)
    set(SCAMS_HOME "/usr/local/systemc-ams/")
endif ()
message("Env variable SCAMS_HOME = " ${SCAMS_HOME})

set(CMAKE_BUILD_TYPE RelWithDebInfo)

include_directories(${SYSTEMC_HOME}/include)
include_directories(${SCAMS_HOME}/include)
include_directories(Solutions/Heterogeneous_Platform/include)
include_directories(Solutions/Continuous_Subsystem/include)
include_directories(Solutions/HW_Subsystem/AT4/include)
include_directories(Solutions/HW_Subsystem/LT/include)
include_directories(Solutions/HW_Subsystem/RTL/include)
include_directories(Solutions/HW_Subsystem/UT/include)

find_library(systemc systemc ${SYSTEMC_HOME}/lib-linux64)
find_library(systemc-ams systemc-ams ${SCAMS_HOME}/lib-linux64)
link_directories(${SYSTEMC_HOME}/lib-linux64)
link_directories(${SCAMS_HOME}/lib-linux64)

add_executable(heterogeneous_platform.x
        Solutions/Heterogeneous_Platform/src/main.cpp
        Solutions/Heterogeneous_Platform/src/Controller.cpp
        Solutions/Heterogeneous_Platform/src/Controller.cpp
        Solutions/Heterogeneous_Platform/src/Tank_iface.cpp
        Solutions/Heterogeneous_Platform/src/Tank.cpp
        Solutions/Heterogeneous_Platform/src/Transactor_tank.cpp
        Solutions/Heterogeneous_Platform/src/Transactor_xtea.cpp
        Solutions/Heterogeneous_Platform/src/Valve_iface.cpp
        Solutions/Heterogeneous_Platform/src/Valve.cpp
        Solutions/Heterogeneous_Platform/src/Wt_system.cpp
        Solutions/Heterogeneous_Platform/src/Xtea.cpp)

add_executable(continuous_subsystem.x
        Solutions/Continuous_Subsystem/src/mainC.cpp
        Solutions/Continuous_Subsystem/src/ControllerC.cpp
        Solutions/Continuous_Subsystem/src/TankC.cpp
        Solutions/Continuous_Subsystem/src/ValveC.cpp)

add_executable(hw_subsystem_AT4.x
        Solutions/HW_Subsystem/AT4/src/main_xtea_AT4.cpp
        Solutions/HW_Subsystem/AT4/src/xtea_AT4.cpp
        Solutions/HW_Subsystem/AT4/src/xtea_AT4_testbench.cpp)

add_executable(hw_subsystem_LT.x
        Solutions/HW_Subsystem/LT/src/main_xtea_LT.cpp
        Solutions/HW_Subsystem/LT/src/xtea_LT.cpp
        Solutions/HW_Subsystem/LT/src/xtea_LT_testbench.cpp)

add_executable(hw_subsystem_RTL.x
        Solutions/HW_Subsystem/RTL/src/main_xtea_RTL.cpp
        Solutions/HW_Subsystem/RTL/src/xtea_RTL.cpp
        Solutions/HW_Subsystem/RTL/src/xtea_RTL_testbench.cpp)

add_executable(hw_subsystem_UT.x
        Solutions/HW_Subsystem/UT/src/main_xtea_UT.cpp
        Solutions/HW_Subsystem/UT/src/xtea_UT.cpp
        Solutions/HW_Subsystem/UT/src/xtea_UT_testbench.cpp)

target_link_libraries(heterogeneous_platform.x systemc systemc-ams)
target_link_libraries(continuous_subsystem.x systemc systemc-ams)
target_link_libraries(hw_subsystem_AT4.x systemc)
target_link_libraries(hw_subsystem_LT.x systemc)
target_link_libraries(hw_subsystem_RTL.x systemc)
target_link_libraries(hw_subsystem_UT.x systemc)