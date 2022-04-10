include_guard()
include(WorkspaceUtilities)

set(NUGET_MICROSOFT_WINDOWS_CPPWINRT_VERSION "2.0.220325.3" CACHE STRING "Microsoft.Windows.CppWinRT nuget package version")
set(NUGET_MICROSOFT_WINDOWSAPPSDK_VERSION "1.1.0-preview1" CACHE STRING "Microsoft.WindowsAppSDK nuget package version")
set(NUGET_MICROSOFT_WINDOWS_SDK_BUILDTOOLS_VERSION "10.0.22593-preview" CACHE STRING "Microsoft.Windows.SDK.BuildTools nuget package version")

set(
  nuget_packages
  Microsoft.Windows.CppWinRT
  Microsoft.Windows.SDK.BuildTools
  Microsoft.WindowsAppSDK
)

function(setup_msvc)
  if (NOT WIN32)
    return()
  endif ()

  if (NOT DEFINED NUGET_PACKAGES_DIR)
    cmake_path(
      APPEND
      CMAKE_BINARY_DIR
      packages
      OUTPUT_VARIABLE dir
    )

    set(NUGET_PACKAGES_DIR ${dir} CACHE STRING "Nuget package directory")
  endif ()


  message("Restoring nuget packages")
  cmake_path(
    APPEND
    CMAKE_CURRENT_FUNCTION_LIST_DIR
    config
    packages.config
    OUTPUT_VARIABLE input
  )
  configure_file(${input} ${NUGET_PACKAGES_DIR}.config @ONLY)

  execute_process(
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND nuget
    restore
    -PackagesDirectory
    ${NUGET_PACKAGES_DIR}
  )
  message("Nuget packages restored")

  configure_vs_directory_props()
endfunction()

function(configure_vs_directory_props)
  if (NOT WIN32)
    return()
  endif ()

  if (NOT DEFINED NUGET_PACKAGES_DIR)
    cmake_path(
      APPEND
      CMAKE_BINARY_DIR
      packages
      OUTPUT_VARIABLE dir
    )

    set(NUGET_PACKAGES_DIR ${dir} CACHE STRING "Nuget package directory")
  endif ()

   set(
    prop_extensions
    "props"
    "targets"
  )

  make_cmake_binary_path(
    GeneratedFilesDir
     generated
  )


  foreach(package IN LISTS nuget_packages)
    string(MAKE_C_IDENTIFIER "${package}" package_var)
    string(JOIN "_" package_var nuget ${package_var} version)
    string(TOUPPER ${package_var} package_var)
    if(NOT DEFINED ${package_var})
      message(FATAL_ERROR "Package version for ${package} not defined ${package_var}")
    endif()
    string(JOIN "." package_dir "${package}" "${${package_var}}")
    cmake_path(
      APPEND
      NUGET_PACKAGES_DIR
      ${package_dir}
      OUTPUT_VARIABLE package_dir
    )

    if(NOT EXISTS ${package_dir})
      message(FATAL_ERROR "Package ${package} not installed")
    endif()

    foreach(extension IN LISTS prop_extensions)
      string(JOIN "." file "${package}" ${extension})
      cmake_path(
        APPEND
        package_dir
        build
        native
        ${file}
        OUTPUT_VARIABLE file
      )
      string(APPEND import_${extension} "<Import Project=\"${file}\" Condition=\"EXISTS('${file}')\"/>")
    endforeach()
  endforeach()

  foreach(extension IN LISTS prop_extensions)
    string(JOIN "." file "Directory.Build" ${extension})
    cmake_path(
      APPEND
      CMAKE_CURRENT_FUNCTION_LIST_DIR
      config
      ${file}
      OUTPUT_VARIABLE input
    )
    cmake_path(
      APPEND
      CMAKE_BINARY_DIR
      ${file}
      OUTPUT_VARIABLE output
    )
    configure_file(${input} ${output} @ONLY)
  endforeach()
endfunction()

function(configure_vs_app_manifest target)
  if (NOT WIN32)
    return()
  endif ()
  cmake_path(
    APPEND
    CMAKE_CURRENT_FUNCTION_LIST_DIR
    config
    app.manifest
    OUTPUT_VARIABLE input
  )
  cmake_path(
    APPEND
    CMAKE_CURRENT_BINARY_DIR
    app.manifest
    OUTPUT_VARIABLE output
  )
  configure_file(${input} ${output} @ONLY)
  target_sources(
    ${target}
    PRIVATE
    ${output}
  )

endfunction()
