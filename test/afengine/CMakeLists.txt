test_target(
  AFEngine
  LINK_LIBRARIES
  ${PROJECT_NAME}::AFEngine
)

add_subdirectory(application)
add_subdirectory(foundation)
