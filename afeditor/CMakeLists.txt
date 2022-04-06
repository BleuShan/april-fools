project(
  AFEditor
  VERSION 0.1.0
  LANGUAGES C CXX
)

executable_target(
  AFEditor
  LINK_LIBRARIES
  AFEngine
)

if (WIN32)
  set_target_properties(
    AFEditor
    PROPERTIES
    WIN32_EXECUTABLE ON
  )
endif ()


add_subdirectory(platforms)
