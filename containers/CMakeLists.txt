################### CIRCULAR ARRAY TEST ###############################################
add_executable(CircularArrayTest test/CircularArrayTest.cpp)

target_link_libraries(CircularArrayTest
  libgtest_main.a
  libgtest.a
  pthread
)

add_test(NAME CircularArrayTest COMMAND CircularArrayTest)

################### RING BUFFER TEST ###############################################
add_executable(RingBufferTest test/RingBufferTest.cpp)

target_link_libraries(RingBufferTest
  libgtest_main.a
  libgtest.a
  pthread
)

add_test(NAME RingBufferTest COMMAND RingBufferTest)

################### MPSC Queue TEST ###############################################
add_executable(MpscQueueTest test/MpscQueueTest.cpp)

target_link_libraries(MpscQueueTest
  libgtest_main.a
  libgtest.a
  pthread
)

add_test(NAME MpscQueueTest COMMAND MpscQueueTest)

################### Performance Metric ###############################################
add_executable(Perf test/Performance.cpp)

target_link_libraries(Perf
  pthread
)

