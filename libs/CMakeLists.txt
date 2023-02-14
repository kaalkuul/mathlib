add_subdirectory(mathlib)

if (MATHLIB_BUILD_TEST_LIB)
	add_subdirectory(testlib)
endif()
