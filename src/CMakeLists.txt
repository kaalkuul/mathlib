add_library(mathlib STATIC
  ../include/mathlib.h
  ../include/common.h
  ../include/constants.h
  ../include/functions.h
  ../include/interpolation.h
  ../include/vec2.h
  ../include/vec3.h
  ../include/quat.h
  ../include/mat2.h
  ../include/mat3.h
  ../include/mat34.h
  ../include/impl/constants.h
  ../include/impl/vec2.h
  ../include/impl/vec3.h
  ../include/impl/quat.h
  ../include/impl/mat2.h
  ../include/impl/mat3.h
  ../include/impl/mat34.h
  mathlib.cpp
)

add_library(mathlib::mathlib ALIAS mathlib)

target_include_directories(mathlib
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
