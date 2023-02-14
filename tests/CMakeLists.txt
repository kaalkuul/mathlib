if(NOT TARGET Catch2::Catch2)
	find_package(Catch2 3 REQUIRED)
endif()

add_subdirectory(tests)
