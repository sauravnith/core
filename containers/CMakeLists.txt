################### CIRCULAR ARRAY TEST ###############################################
add_executable(CircularArrayTest test/CircularArrayTest.cpp)

target_include_directories( CircularArrayTest PUBLIC ${GTEST_INCLUDE_DIR})

target_link_libraries(CircularArrayTest
        ${GTEST_LIB}
        pthread
        )

add_test(NAME CircularArrayTest COMMAND CircularArrayTest)

################### RING BUFFER TEST ###############################################
#add_executable(RingBufferTest test/RingBufferTest.cpp)

#target_link_libraries(RingBufferTest
#  libgtest_main.a
#  libgtest.a
#  pthread
#)

#add_test(NAME RingBufferTest COMMAND RingBufferTest)