include(FindPackageHandleStandardArgs)

if(NOT GTEST_ROOT)
    SET(GTEST_ROOT "${TOOLS_HOME}/gtest")
endif()

if(GTEST_ROOT)
    message(STATUS "GTEST_ROOT: ${GTEST_ROOT}")
    SET(GTEST_INCLUDE_PATHS PATHS "${GTEST_ROOT}/include" NO_DEFAULT_PATH)
    SET(GTEST_LIBRARY_PATHS PATHS "${GTEST_ROOT}/lib" NO_DEFAULT_PATH)
endif()

SET(GTEST_LIB libgtest_main.a libgtest.a)

find_path(GTEST_INCLUDE_DIR NAMES gtest/gtest.h ${GTEST_INCLUDE_PATHS})
find_path(GTEST_LIBRARY_DIR NAMES ${GTEST_LIB} ${GTEST_LIBRARY_PATHS})

find_package_handle_standard_args(GTEST REQUIRED_VARS GTEST_LIB GTEST_INCLUDE_DIR GTEST_LIBRARY_DIR)

if(GTEST_FOUND)
    message(STATUS "GTEST_INCLUDE_DIR: ${GTEST_INCLUDE_DIR}")
    message(STATUS "GTEST_LIBRARY_DIR: ${GTEST_LIBRARY_DIR}")
endif()