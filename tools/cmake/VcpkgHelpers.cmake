include_guard()

include(CMakeDependentOption)
include(WorkspaceUtilities)

function(setup_vcpkg)
  if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT
      $ENV{VCPKG_ROOT}
      CACHE STRING "Vcpkg root directory")
  elseif (NOT DEFINED VCPKG_ROOT)
    set(VCPKG_ROOT
      ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg
      CACHE STRING "Vcpkg root directory")
  endif ()

  if (VCPKG_ROOT STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}/tools/vcpkg")
    set(LOCAL_VCPKG_ROOT ON)
  endif ()


  set(VCPKG_EXECUTABLE
    ${VCPKG_ROOT}/vcpkg
    CACHE STRING "Vcpkg executable")

  set(VCPKG_BOOTSTRAP_SCRIPT
    ${VCPKG_ROOT}/bootstrap-vcpkg.sh
    CACHE STRING "Vcpkg bootstrap script"
    )

  set(VCPKG_MANIFEST_DIR
    ${CMAKE_SOURCE_DIR}
    CACHE STRING "Vcpkg manifest directory"
    )
  cmake_path(APPEND VCPKG_MANIFEST_DIR vcpkg.json OUTPUT_VARIABLE manifest_file)
  set(VCPKG_MANIFEST_FILE
    ${manifest_file}
    CACHE STRING "Vcpkg manifest filepath"
    )

  cmake_dependent_option(
    VCPKG_MANIFEST_MODE
    OFF
    "Toogles vcpkg manifest mode"
    "EXISTS VCPKG_MANIFEST_FILE;NOT EXISTS VCPKG_MANIFEST_FILE"
    ON
  )

  cmake_dependent_option(
    VCPKG_MANIFEST_INSTALL
    OFF
    "Toogles vcpkg manifest mode"
    "VCPKG_MANIFEST_MODE;NOT VCPKG_MANIFEST_MODE"
    ON
  )


  if (CMAKE_HOST_WIN32)
    set(VCPKG_EXECUTABLE
      ${VCPKG_EXECUTABLE}.exe
      CACHE STRING "Vcpkg executable")

    set(VCPKG_BOOTSTRAP_SCRIPT
      ${VCPKG_ROOT}/bootstrap-vcpkg.bat
      CACHE STRING "Vcpkg bootstrap script"
      )
  endif ()

  if (DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED VCPKG_TARGET_TRIPLET)
    set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET} CACHE STRING "")
  endif ()

  set(CMAKE_TOOLCHAIN_FILE
    ${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

  if (LOCAL_VCPKG_ROOT)
    execute_process(
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      COMMAND git
      submodule
      update
      "--init"
      "--recursive"
    )
  endif ()

  if (NOT EXISTS ${VCPKG_EXECUTABLE})
    execute_process(COMMAND ${VCPKG_BOOTSTRAP_SCRIPT})
  endif ()

  mark_as_advanced(FORCE
    CMAKE_TOOLCHAIN_FILE
    VCPKG_EXECUTABLE
    VCPKG_BOOTSTRAP_SCRIPT
    VCPKG_LINKAGE
    )
endfunction()

function(setup_vcpkg_features)
  set(features ${VCPKG_MANIFEST_FEATURES})
  if (BUILD_TESTING)
    list(APPEND features tests)
  endif ()
  list(REMOVE_ITEM features ${WORKSPACE_SUPPORTED_TARGET_OSES})
  string(TOLOWER ${TARGET_OS} system)
  list(APPEND features ${system})
  string(JOIN ";" features ${features})
  set(VCPKG_MANIFEST_FEATURES ${features} CACHE INTERNAL "Enabled manifest features")
endfunction()
