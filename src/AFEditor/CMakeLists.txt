executable_target(
  AFEditor
  LINK_LIBRARIES
  ${PROJECT_NAME}::AFEngine
)

if(WIN32)
  set_target_properties(
    AFEditor
    PROPERTIES
    WIN32_EXECUTABLE ON
  )
endif()


add_subdirectory(Platforms)
