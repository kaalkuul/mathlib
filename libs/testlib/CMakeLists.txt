if(NOT TARGET Catch2::Catch2)
	find_package(Catch2 3 REQUIRED)
endif()

add_library(mathlib_testlib INTERFACE
	include/mathlib_testlib.h
	include/impl/catch_matchers.h
	include/impl/catch_matchers_colorrgb.h
	include/impl/catch_matchers_colorrgba.h
	include/impl/catch_matchers_colorhsv.h
	include/impl/catch_matchers_vec2.h
	include/impl/catch_matchers_vec3.h
	include/impl/catch_matchers_vec4.h
	include/impl/catch_matchers_mat2.h
	include/impl/catch_matchers_mat3.h
	include/impl/catch_matchers_mat4.h
	include/impl/catch_matchers_mat34.h
	include/impl/catch_matchers_quat.h
)

add_library(mathlib::testlib ALIAS mathlib_testlib)

set_target_properties(mathlib_testlib PROPERTIES
	OUTPUT_NAME mathlib_testlib
	EXPORT_NAME testlib
)

target_link_libraries(mathlib_testlib
	INTERFACE
		mathlib
)

set_property(TARGET mathlib_testlib PROPERTY FOLDER "Tests")

target_include_directories(mathlib_testlib
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(MATHLIB_INSTALL)
	install(
		TARGETS mathlib_testlib
		EXPORT mathlib-targets
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	install(
		DIRECTORY include/
		DESTINATION ${MATHLIB_INSTALL_INCLUDEDIR}/testlib
	)
endif()
