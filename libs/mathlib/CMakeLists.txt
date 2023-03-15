add_library(mathlib INTERFACE
  include/mathlib.h
  include/common.h
  include/constants.h
  include/functions.h
  include/interpolation.h
  include/colorrgb.h
  include/colorrgba.h
  include/vec2.h
  include/vec3.h
  include/quat.h
  include/mat2.h
  include/mat3.h
  include/mat34.h
  include/impl/constants.h
  include/impl/colorrgb.h
  include/impl/colorrgba.h
  include/impl/vec2.h
  include/impl/vec3.h
  include/impl/quat.h
  include/impl/mat2.h
  include/impl/mat3.h
  include/impl/mat34.h
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
