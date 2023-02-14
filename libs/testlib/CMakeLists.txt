if(NOT TARGET Catch2::Catch2)
	find_package(Catch2 3 REQUIRED)
endif()

add_library(testlib INTERFACE
	include/mathlib_testlib.h
	include/impl/catch_matchers.h
	include/impl/catch_matchers_vec2.h
	include/impl/catch_matchers_vec3.h
	include/impl/catch_matchers_mat2.h
	include/impl/catch_matchers_mat3.h
	include/impl/catch_matchers_mat34.h
	include/impl/catch_matchers_quat.h
)

add_library(mathlib::testlib ALIAS testlib)

target_link_libraries(testlib
	INTERFACE
		mathlib
)

set_property(TARGET testlib PROPERTY FOLDER "Tests")

target_include_directories(testlib
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(MATHLIB_INSTALL)
	install(
		TARGETS testlib
		EXPORT mathlib-targets
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
	install(
		DIRECTORY include/
		DESTINATION ${MATHLIB_INSTALL_INCLUDEDIR}/testlib
	)
endif()
