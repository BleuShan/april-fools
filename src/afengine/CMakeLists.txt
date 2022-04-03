find_package(Folly CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(directX-headers CONFIG)
find_package(directxmath CONFIG)

library_target(
  AFEngine
  LINK_LIBRARIES
  PUBLIC
  Folly::folly
  Folly::folly_deps
  absl::btree
  absl::cord
  imgui::imgui
)

target_link_libraries(
  AFEngine
  PUBLIC
  "$<$<IN_LIST:windows,${VCPKG_MANIFEST_FEATURES}>:Microsoft::DirectX-Guids>"
  "$<$<IN_LIST:windows,${VCPKG_MANIFEST_FEATURES}>:Microsoft::DirectX-Headers>"
  "$<$<IN_LIST:windows,${VCPKG_MANIFEST_FEATURES}>:Microsoft::DirectXMath>"
)


set_target_properties(
  AFEngine
  PROPERTIES
  VS_WINRT_REFERENCES "windows"
  VS_PROJECT_IMPORT "${NUGET_MICROSOFT_WINDOWS_CPPWINRT_IMPORTS}"
)

add_sources(
  PUBLIC
  afengine.h
)

configure_target_file()

add_subdirectory(application)
add_subdirectory(foundation)
