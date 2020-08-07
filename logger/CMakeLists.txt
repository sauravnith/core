
set(log_SOURCES
	Sink.cpp
	Logger.cpp
)

add_library(core_log STATIC ${log_SOURCES})

########Test###################
add_executable(LogTest
	test/LogTest.cpp
	Logger.cpp
	Sink.cpp
)



