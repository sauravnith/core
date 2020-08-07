################### CIRCULAR ARRAY TEST ###############################################
add_executable(CircularArrayTest test/CircularArrayTest.cpp)

target_include_directories( CircularArrayTest PUBLIC ${GTEST_INCLUDE_DIR})

target_link_libraries(CircularArrayTest
        ${GTEST_LIB}
        pthread
        )

add_test(NAME CircularArrayTest COMMAND CircularArrayTest)

################### RING BUFFER TEST ###############################################
add_executable(RingBufferTest test/RingBufferTest.cpp)

target_include_directories( RingBufferTest PUBLIC ${GTEST_INCLUDE_DIR})
target_link_libraries(RingBufferTest
  ${GTEST_LIB}
  pthread
)

add_test(NAME RingBufferTest COMMAND RingBufferTest)

################### MPSC Queue TEST ###############################################
add_executable(MpscQueueTest test/MpscQueueTest.cpp)

target_link_libraries(MpscQueueTest ${GTEST_LIB} pthread)

add_test(NAME MpscQueueTest COMMAND MpscQueueTest)

################### Performance Metric ###############################################
add_executable(Perf test/Performance.cpp)

target_link_libraries(Perf
  pthread
)

