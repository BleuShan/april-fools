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

if(APPLE)
  set_target_properties(
    AFEditor
    PROPERTIES
    OBJC_STANDARD 11
    OBJCXX_STANDARD 23
  )
endif()


add_subdirectory(platforms)
