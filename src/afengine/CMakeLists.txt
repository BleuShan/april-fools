find_package(Folly CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)

library_target(
  AFEngine
  LINK_LIBRARIES
  PUBLIC
  Folly::folly
  Folly::folly_deps
  absl::btree
  absl::optional
  imgui::imgui
)

add_sources(
  PUBLIC
  afengine.h
)

configure_file_target_file()

add_subdirectory(application)
add_subdirectory(foundation)
