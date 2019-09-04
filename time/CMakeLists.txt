
add_custom_target(time DEPENDS
	core_log
)

set(time_SOURCES
	Clock.cpp
)

add_library(core_time STATIC ${time_SOURCES})

target_link_libraries(core_time
					  core_log
)

##########TEST########################
add_executable(sampleClock
	test/sampleClock.cpp
	Clock.cpp
)

target_link_libraries(sampleClock
		core_time)



