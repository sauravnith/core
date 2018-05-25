add_executable(MemPoolTest test/MemPoolTest.cpp)

target_link_libraries(MemPoolTest
  libgtest_main.a
  libgtest.a
  pthread
)

add_test(NAME MemPoolTest COMMAND MemPoolTest)
