cmake_minimum_required(VERSION 3.2.3)
  
#-------------DEPENDENCIES ---------------------
if(DEFINED ENV{TOOLS_HOME})
  set(TOOLS_HOME "$ENV{TOOLS_HOME}")
else()
  set(TOOLS_HOME "/usr/local/Cellar")
endif()

message(STATUS "TOOLS_HOME:      ${TOOLS_HOME}")
#-------------DEPENDENCIES---------------------

#-------------COMPILER FLAGS---------------------
set(COMMON_FLAGS "-march=core2 -fno-var-tracking")
set(COMMON_WARN "-Wall -Wextra -Werror -Wno-unused-function -Wno-deprecated-declarations -Wno-sign-compare -Wno-unused-parameter -Wignored-qualifiers -Wtype-limits -Wduplicated-cond -Wimplicit-fallthrough=0")
#-------------COMPILER FLAGS---------------------

#-------------CMAKE FLAGS---------------------

set(CMAKE_BUILD_TYPE DEBUG)
#set(CMAKE_BUILD_TYPE RELEASE)
#set(CMAKE_BUILD_TYPE RELWITHDEBINFO)
#set(CMAKE_BUILD_TYPE MINSIZEREL)
#set(CMAKE_BUILD_TYPE PERF)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${COMMON_WARN}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${COMMON_WARN}")

#-------------CMAKE FALGS---------------------

#-------------HEADERS---------------------

include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}
 "${TOOLS_HOME}"
)

#-------------LINKER---------------------


#link_directories(
#  "${TOOLS_HOME}/lib64"
#)

#-------------UNIT TESTS---------------------

enable_testing()
macro(test_help target)
add_test(NAME "${target}_HelpTest" COMMAND ${target} --help)
endmacro()

#-------------UNIT TESTS---------------------

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

add_subdirectory(containers)
add_subdirectory(logger)
add_subdirectory(utils)
add_subdirectory(transport)
add_subdirectory(log)
