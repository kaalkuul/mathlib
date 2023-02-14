cmake_minimum_required(VERSION 3.20)

project(testing)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.2.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

find_package(mathlib REQUIRED)

add_executable(testing
	src/main.cpp
	src/tests.cpp
)

target_link_libraries(testing
	PRIVATE
		mathlib::mathlib
		mathlib::testlib
		Catch2::Catch2
)
