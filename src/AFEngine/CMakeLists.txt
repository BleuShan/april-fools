find_package(Folly CONFIG REQUIRED)

library_project(
  AFEngine
  LINK_LIBRARIES
  Folly::folly
  Folly::folly_deps
)

add_sources(
  PUBLIC
  AFEngine.h
  PRIVATE
  AFEngine.cc
)

add_subdirectory(Application)


if(BUILD_TESTING)
  enable_testing()
  include(Dart)
  include(GoogleTest)
  find_package(GTest CONFIG REQUIRED)
endif()
