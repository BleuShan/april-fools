if(WORKSPACE_TARGET_OS STREQUAL Windows)
  add_subdirectory(Windows)
endif()

if(WORKSPACE_TARGET_OS STREQUAL macOS)
  add_subdirectory(macOS)
endif()
