add_executable(MemPoolTest test/MemPoolTest.cpp)

target_include_directories( MemPoolTest PUBLIC ${GTEST_INCLUDE_DIR})

target_link_libraries(MemPoolTest
  ${GTEST_LIB}
  pthread
)

add_test(NAME MemPoolTest COMMAND MemPoolTest)
