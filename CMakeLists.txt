cmake_minimum_required(VERSION 3.22)
set(
  CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake
  ${CMAKE_MODULE_PATH}
)

include(Workspace)

project(${WORKSPACE_PACKAGE_NAME})

add_subdirectory(src)
