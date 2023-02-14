if (MATHLIB_BUILD_TEST_LIB OR MATHLIB_BUILD_TESTS)
  find_package(Catch2 3 QUIET)

  if (NOT TARGET Catch2::Catch2)
    message("Catch2 not found. Using FetchContent to make it available locally.")
    
    Include(FetchContent)

    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.2.1 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)
  endif()
endif()
