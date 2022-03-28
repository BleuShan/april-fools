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

if(WORKSPACE_TARGET_OS STREQUAL macOS)
  set_target_properties(
    AFEditor
    PROPERTIES
    OBJC_STANDARD 11
    OBJCXX_STANDARD 23
  )
endif()


add_subdirectory(Platforms)
