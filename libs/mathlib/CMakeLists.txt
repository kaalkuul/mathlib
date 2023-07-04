add_library(mathlib INTERFACE
  include/mathlib.h
  include/common.h
  include/constants.h
  include/functions.h
  include/interpolation.h
  include/linearequations.h
  include/colorrgb.h
  include/colorrgba.h
  include/colorhsv.h
  include/aabb.h
  include/vec2.h
  include/vec3.h
  include/vec4.h
  include/quat.h
  include/mat2.h
  include/mat3.h
  include/mat4.h
  include/mat34.h
  include/line2.h
  include/line3.h
  include/ray2.h
  include/ray3.h
  include/plane.h
  include/sphere.h
  include/spline3.h
  include/impl/constants.h
  include/impl/linearequations.h
  include/impl/colorrgb.h
  include/impl/colorrgba.h
  include/impl/colorhsv.h
  include/impl/aabb.h
  include/impl/vec2.h
  include/impl/vec3.h
  include/impl/vec4.h
  include/impl/quat.h
  include/impl/mat2.h
  include/impl/mat3.h
  include/impl/mat4.h
  include/impl/mat34.h
  include/impl/line2.h
  include/impl/line3.h
  include/impl/ray2.h
  include/impl/ray3.h
  include/impl/plane.h
  include/impl/sphere.h
  include/impl/spline3.h
)

add_library(mathlib::mathlib ALIAS mathlib)

target_include_directories(mathlib
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/mathlib>
)

if(MATHLIB_INSTALL)
  install(TARGETS mathlib
      EXPORT mathlib-targets
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
  install(
    DIRECTORY include/
    DESTINATION ${MATHLIB_INSTALL_INCLUDEDIR}
  )
endif()
