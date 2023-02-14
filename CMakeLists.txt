cmake_minimum_required(VERSION 3.20)

project(mathlib VERSION 1.0.0 LANGUAGES CXX)

set(mathlib_AUTHOR https://github.com/eboutin/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MATHLIB_IS_MAIN_PROJECT FALSE)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(MATHLIB_IS_MAIN_PROJECT TRUE)
endif()
message(STATUS "mathlib is main project: ${MATHLIB_IS_MAIN_PROJECT}")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

option(MATHLIB_BUILD_TEST_LIB "Enable test library for mathlib" ON)
option(MATHLIB_BUILD_TESTS "Enable testing for mathlib" ${MATHLIB_IS_MAIN_PROJECT})
option(MATHLIB_INSTALL "Install mathlib files" ${MATHLIB_IS_MAIN_PROJECT})

add_subdirectory(deps)

if(MATHLIB_INSTALL)
  include(GNUInstallDirs)
  set(MATHLIB_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/mathlib")
  set(MATHLIB_INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/mathlib)
endif()

add_subdirectory(libs)

if (MATHLIB_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(MATHLIB_INSTALL)
  #Export the targets to a script
  install(EXPORT mathlib-targets
    FILE
      mathlib-targets.cmake
    NAMESPACE
      mathlib::
    DESTINATION
      ${MATHLIB_INSTALL_CONFIGDIR}
  )

  #Create a ConfigVersion.cmake file
  include(CMakePackageConfigHelpers)

  write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/mathlib-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
  )

  configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/mathlib-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/mathlib-config.cmake
    INSTALL_DESTINATION ${MATHLIB_INSTALL_CONFIGDIR}
  )

  #Install the config, configversion and custom find modules
  install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/mathlib-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/mathlib-config-version.cmake
    DESTINATION ${MATHLIB_INSTALL_CONFIGDIR}
  )

  ## Exporting from the build tree
  export(EXPORT mathlib-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/mathlib-targets.cmake
    NAMESPACE mathlib::
  )

  #Register package in the User Package Registry
  export(PACKAGE mathlib)
endif()
