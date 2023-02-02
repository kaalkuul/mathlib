add_library(mathlib_testlib
	include/mathlib_testlib.h
	include/impl/catch_matchers.h
	include/impl/catch_matchers_vec2.h
	include/impl/catch_matchers_vec3.h
	include/impl/catch_matchers_mat2.h
	include/impl/catch_matchers_mat3.h
	include/impl/catch_matchers_mat34.h
	include/impl/catch_matchers_quat.h
	src/mathlib_testlib.cpp
)

add_library(mathlib::testlib ALIAS mathlib_testlib)

target_link_libraries(mathlib_testlib Catch2::Catch2 mathlib)

set_property(TARGET mathlib_testlib PROPERTY FOLDER "Tests")

target_include_directories(mathlib_testlib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
