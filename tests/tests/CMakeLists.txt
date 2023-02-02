add_executable(mathlib_tests
	src/main.cpp
	src/utils.h src/utils.cpp
	src/test_functions.cpp
	src/test_interpolation.cpp
	src/test_vec2.cpp
	src/test_vec3.cpp
	src/test_quat.cpp
	src/test_mat2.cpp
	src/test_mat3.cpp
	src/test_mat34.cpp
)

target_compile_definitions(mathlib_tests
	PRIVATE
	TEST_DATA_DIR=R"\(${TEST_DATA_DIR}\)"
	CATCH_CONFIG_FAST_COMPILE DO_NOT_USE_WMAIN)

target_link_libraries(mathlib_tests Catch2::Catch2 mathlib mathlib_testlib)

set_property(TARGET mathlib_tests PROPERTY FOLDER "Tests")

enable_testing()

add_test(mathlib_tests mathlib_tests ${CATCH_EXTRA_ARGS})
