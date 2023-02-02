find_package(Catch2 3 QUIET)

if (NOT Catch2_FOUND)
	message("Catch2 not found. Using FetchContent to make Catch2 available locally.")
	
	Include(FetchContent)

	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v3.2.1 # or a later release
	)

	FetchContent_MakeAvailable(Catch2)
endif()

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

if (MATHLIB_BUILD_TEST_LIB)
	message("Adding testlib directory.")
	add_subdirectory(testlib)
endif()

if (MATHLIB_BUILD_TESTING)
	message("Adding tests directory.")
	enable_testing()
  add_subdirectory(tests)
endif()
