add_sources(
  PUBLIC
  platform.h
)

add_subdirectory(core)

list_contains(VCPKG_MANIFEST_FEATURES macos supports_macos)

if (supports_macos)
  add_subdirectory(macos)
endif ()


list_contains(VCPKG_MANIFEST_FEATURES windows supports_windows)

if (supports_windows)
  add_subdirectory(windows)
endif ()