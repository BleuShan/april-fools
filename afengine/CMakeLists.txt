project(
  AFEngine
  VERSION 0.1.0.0
  LANGUAGES C CXX
)

find_package(Folly CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(mimalloc CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)

list_contains(VCPKG_MANIFEST_FEATURES windows supports_windows)

if (supports_windows)
  find_package(directX-headers CONFIG REQUIRED)
  find_package(directxmath CONFIG REQUIRED)
endif ()

library_target(
  ${PROJECT_NAME}
  LINK_LIBRARIES
  PRIVATE
  Folly::folly
  Folly::folly_deps
  absl::btree
  absl::cord
  imgui::imgui
  mimalloc
  Microsoft.GSL::GSL
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  "$<$<IN_LIST:windows,${VCPKG_MANIFEST_FEATURES}>:Microsoft::DirectX-Guids>"
  "$<$<IN_LIST:windows,${VCPKG_MANIFEST_FEATURES}>:Microsoft::DirectX-Headers>"
  "$<$<IN_LIST:windows,${VCPKG_MANIFEST_FEATURES}>:Microsoft::DirectXMath>"
  "$<$<IN_LIST:macos, ${VCPKG_MANIFEST_FEATURES}>:-framework Foundation>"
  "$<$<IN_LIST:macos, ${VCPKG_MANIFEST_FEATURES}>:-framework AppKit>"
)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  VS_WINRT_REFERENCES "windows"
  VS_PROJECT_IMPORT "${NUGET_MICROSOFT_WINDOWS_CPPWINRT_IMPORTS}"
)

add_sources(
  PUBLIC
  afengine.h
)

add_subdirectory(macros)
add_subdirectory(application)
add_subdirectory(foundation)
add_subdirectory(runtime)

if (BUILD_TESTING)
  enable_testing()
  include(Dart)
  include(GoogleTest)
  find_package(GTest CONFIG REQUIRED)
  add_subdirectory(tests)
endif ()
