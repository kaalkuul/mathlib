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

add_executable(mathlib_tests
	src/utils.h src/utils.cpp
	src/matchers/catch_matchers.h
	src/matchers/catch_matchers_vec2.h
	src/matchers/catch_matchers_vec3.h
	src/matchers/catch_matchers_mat2.h
	src/matchers/catch_matchers_mat3.h
	src/matchers/catch_matchers_quat.h
	src/main.cpp
	src/test_functions.cpp
	src/test_interpolation.cpp
	src/test_vec2.cpp
	src/test_vec3.cpp
	src/test_quat.cpp
	src/test_mat2.cpp
	src/test_mat3.cpp
	src/test_mat34.cpp
)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

target_compile_definitions(mathlib_tests
	PRIVATE
	TEST_DATA_DIR=R"\(${TEST_DATA_DIR}\)"
	CATCH_CONFIG_FAST_COMPILE DO_NOT_USE_WMAIN)

target_link_libraries(mathlib_tests Catch2::Catch2 mathlib)

set_property(TARGET mathlib_tests PROPERTY FOLDER "Tests")

enable_testing()

add_test(mathlib_tests mathlib_tests ${CATCH_EXTRA_ARGS})
