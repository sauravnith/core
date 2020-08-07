##########TEST########################
add_executable(sampleClock
	test/sampleClock.cpp
	Clock.cpp
)

target_link_libraries(sampleClock
		core_log)



