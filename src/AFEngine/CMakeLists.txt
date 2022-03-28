find_package(Folly CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

library_target(
  AFEngine
  LINK_LIBRARIES
  Folly::folly
  Folly::folly_deps
  imgui::imgui
)

add_sources(
  PUBLIC
  AFEngine.h
)

add_subdirectory(Application)
add_subdirectory(Foundation)