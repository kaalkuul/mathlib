cmake_minimum_required(VERSION 3.20)

project(integration)

find_package(mathlib REQUIRED)

add_executable(integration
	src/main.cpp
)

target_link_libraries(integration
	PRIVATE
		mathlib::mathlib
)
