cmake_minimum_required(VERSION 3.21)
set(
  CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake
  ${CMAKE_MODULE_PATH}
)

include(Workspace)

project(AprilsFools
  VERSION 0.1.0
  LANGUAGES C CXX)

include(WorkspaceOptions)

setup_msvc()
add_subdirectory(afengine)
add_subdirectory(afeditor)

