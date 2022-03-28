find_package(Folly CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

library_target(
  afengine
  LINK_LIBRARIES
  Folly::folly
  Folly::folly_deps
  imgui::imgui
)

add_sources(
  PUBLIC
  afengine.h
)

add_subdirectory(application)
add_subdirectory(foundation)
