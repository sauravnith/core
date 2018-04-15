add_library(utils OBJECT
  MemoryPool.cpp
)

add_executable(MemPoolTest test/MemPoolTest.cpp)

target_link_libraries(MemPoolTest
  libboost_unit_test_framework.a
)

add_test(NAME MemPoolTest COMMAND MemPoolTest)