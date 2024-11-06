add_executable(mathlib_tests
	src/main.cpp
	src/utils.h src/utils.cpp
	src/test_functions.cpp
	src/test_interpolation.cpp
	src/test_linearequations.cpp
	src/test_colorrgb.cpp
	src/test_colorrgba.cpp
	src/test_colorhsv.cpp
	src/test_aabb2.cpp
	src/test_aabb3.cpp
	src/test_caabb2.cpp
	src/test_caabb3.cpp
	src/test_vec2.cpp
	src/test_vec3.cpp
	src/test_vec4.cpp
	src/test_quat.cpp
	src/test_mat2.cpp
	src/test_mat3.cpp
	src/test_mat4.cpp
	src/test_mat34.cpp
	src/test_line2.cpp
	src/test_line3.cpp
	src/test_ray2.cpp
	src/test_ray3.cpp
	src/test_tri2.cpp
	src/test_plane.cpp
	src/test_circle.cpp
	src/test_sphere.cpp
	src/test_spline3.cpp
	src/test_frustum.cpp
)

target_compile_definitions(mathlib_tests
	PRIVATE
	TEST_DATA_DIR=R"\(${TEST_DATA_DIR}\)"
	CATCH_CONFIG_FAST_COMPILE DO_NOT_USE_WMAIN)

target_link_libraries(mathlib_tests
	PUBLIC
		mathlib::mathlib
		mathlib::testlib
	PRIVATE
		Catch2::Catch2
)

set_property(TARGET mathlib_tests PROPERTY FOLDER "Tests")

add_test(mathlib_tests mathlib_tests ${CATCH_EXTRA_ARGS})
