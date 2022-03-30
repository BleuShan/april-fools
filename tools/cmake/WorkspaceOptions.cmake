include_guard()

include(CMakeDependentOption)
include(WorkspaceUtilities)

cmake_dependent_option(
  BUILD_TESTING
  "Build the testing tree."
  OFF
  "AprilFools_IS_TOP_LEVEL;NOT AprilFools_IS_TOP_LEVEL"
  ON
)

cmake_dependent_option(
  BUILD_SHARED_LIBS
  "Build shared libraries (DLLs)"
  ON
  "AprilFools_IS_TOP_LEVEL;NOT AprilFools_IS_TOP_LEVEL"
  ON
)


set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Set the default configuration buildtype")
set_property(
  CACHE CMAKE_BUILD_TYPE
  PROPERTY
  STRINGS ${CMAKE_CONFIGURATION_TYPES}
)

setup_vcpkg_features()
