include_guard()
include(WorkspaceUtilities)
include(GenerateExportHeader)

macro(workspace_helpers_parse_arguments prefix)
    set(flags
        SHARED
        WIN32
        MACOSX_BUNDLE
    )
    set(args
        VERSION
    )
    set(list_args
       PROPERTIES
       SOURCES
       LINK_LIBRARIES
    )

    make_cmake_variable_name(
        OUTPUT_VARIABLE
        normalized_prefix
        ${prefix})
    cmake_parse_arguments(
        ${normalized_prefix}
        "${flags}"
        "${args}"
        "${list_args}"
        ${ARGN}
    )
endmacro()

function(workspace_helpers_get_parse_arguments_value var prefix suffix)
    make_cmake_variable_name(
        OUTPUT_VARIABLE
        source
        ${prefix}
        ${suffix})
    list(FIND ARGN CACHE index)
    if(index EQUAL -1)
      list(APPEND ARGN PARENT_SCOPE)
    endif()
    set(${var} ${${source}} ${ARGN})
endfunction()

function(workspace_helpers_set_parse_arguments_value prefix suffix)
    make_cmake_variable_name(
        OUTPUT_VARIABLE
        var
        ${prefix}
        ${suffix})
    list(FIND ARGN CACHE index)
    if(index EQUAL -1)
      list(APPEND ARGN PARENT_SCOPE)
    endif()
    set(${var} ${ARGN})
endfunction()

function(workspace_helpers_set_target_version_properties name)
    set(keys
        VERSION
        SOVERSION)

    foreach(key ${keys})
        string(TOLOWER ${key} value_key)
        get_target_property(${value_key} ${name} ${key})

        if (${${value_key}} STREQUAL "${value_key}-NOTFOUND")
            unset(${value_key})
        endif()

        if(NOT DEFINED ${value_key})
          workspace_helpers_get_parse_arguments_value(${value_key} ${name} ${key})
        endif()

        if(NOT DEFINED ${value_key} AND value_key STREQUAL "version")
            set(${value_key} ${PROJECT_VERSION})
        endif()

        if(NOT DEFINED ${value_key} AND value_key STREQUAL "version")
            set(${value_key} ${WORKSPACE_PACKAGE_VERSION})
        endif()

        if(DEFINED version AND
            NOT DEFINED ${value_key} AND
            value_key STREQUAL "soversion")
            string(REPLACE "." ";" version_values ${version})

            foreach(value ${version_values})
                string(JOIN "." ${value_key} ${${value_key}} ${value})
                if(NOT value STREQUAL "0")
                    break()
                endif()
            endforeach()
        endif()

        if(DEFINED ${value_key})
           list(APPEND versions ${key} ${${value_key}})
        endif()
   endforeach()
   set_target_properties(${name} PROPERTIES ${versions})
endfunction()


function(workspace_helpers_set_target_cxx_properties name)
    if(MSVC)
        set(standard 23)
    else()
        set(standard 20)
    endif()

    set_target_properties(
        ${name}
        PROPERTIES
        C_STANDARD ${standard}
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
        CXX_STANDARD ${standard}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VISIBILITY_PRESET hidden
    )

    target_link_libraries(
      ${name}
      PRIVATE
      "$<$<BOOL:${APPLE}>:$<IF:$<STREQUAL ${TARGET_OS},macOS>,-framework Cocoa,-framework UIKit>>"
    )

    target_compile_definitions(
      ${name}
      PUBLIC
      "$<$<AND:$<BOOL:${WIN32}>,$<BOOL:${MSVC}>>:UNICODE;_UNICODE>"
    )
    target_compile_options(
       ${name}
       PUBLIC
       "$<$<AND:$<BOOL:${WIN32}>,$<BOOL:${MSVC}>>:/bigobj;/MP>"
     )

    target_include_directories(
        ${name}
        INTERFACE
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    )
endfunction()

function(workspace_helpers_set_target_pdb_properties name)
  get_target_property(pdb_debug_postfix ${name} DEBUG_POSTFIX)

  if(${pdb_debug_postfix} STREQUAL "pdb_debug_postfix-NOTFOUND")
    unset(pdb_debug_postfix)
  endif()

  set_target_properties(${name}
    PROPERTIES
    PDB_NAME "${name}"
    PDB_NAME_DEBUG "${name}${pdb_debug_postfix}"
    COMPILE_PDB_NAME "${name}"
    COMPILE_PDB_NAME_DEBUG "${name}${pdb_debug_postfix}")
endfunction()

function(workspace_helpers_set_target_output_directory_properties name)
  set_target_properties(
    ${name}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )
endfunction()

function(workspace_helpers_set_target_properties name)
    workspace_helpers_set_target_version_properties(${name})
    workspace_helpers_set_target_cxx_properties(${name})
    workspace_helpers_set_target_output_directory_properties(${name})
    workspace_helpers_set_target_pdb_properties(${name})

    workspace_helpers_get_parse_arguments_value(props ${name} PROPERTIES)
    if(DEFINED props)
        set_target_properties(${name} PROPERTIES ${props})
    endif()
endfunction()

function(workspace_helpers_target_type name var)
  foreach(flag ${workspace_helpers_parse_arguments_flags})
    workspace_helpers_get_parse_arguments_value(present ${name} ${flag})
    if(present)
      set(${var} ${flag} PARENT_SCOPE)
      return()
    endif()
  endforeach()
endfunction()

function(workspace_helpers_resolve_target_sources name)
    set(flags)
    set(args OUTPUT_VARIABLE)
    set(list_args
        ALLOWED_SUBDIRECTORIES
        ALLOWED_FILENAMES
        DISALLOWED_FILENAMES
        DISALLOWED_FILENAME_PATTERNS)

    make_cmake_variable_name(
        OUTPUT_VARIABLE
        prefix
        workspace_helpers_resolve_target_sources)
    cmake_parse_arguments(
        PARSE_ARGV
        1
        ${prefix}
        "${flags}"
        "${args}"
        "${list_args}"
    )

    workspace_helpers_get_parse_arguments_value(
        output_variable
        ${prefix}
        OUTPUT_VARIABLE)

    if(NOT DEFINED output_variable)
        message(FATAL_ERROR "missing OUTPUT_VARIABLE <output_variable>")
    endif()

    workspace_helpers_get_parse_arguments_value(
        allowed_filenames
        ${prefix}
        ALLOWED_FILENAMES)


    string(REGEX REPLACE ${WORKSPACE_TEST_SUFFIX_REGEX} "" name ${name})
    list(APPEND allowed_filenames ${name})
    if(BUILD_TESTING)
        string(JOIN ";" test_suffixes
            "-tests"
            "_tests"
            "-test"
            "_test"
            "Test"
            "Tests"
        )

        foreach(suffix ${test_suffixes})
            string(CONCAT allowed_filename ${name} ${suffix})
            list(APPEND allowed_filenames ${allowed_filename})
        endforeach()
    endif()

    workspace_helpers_get_parse_arguments_value(
        allowed_subdirectories
        ${prefix}
        ALLOWED_SUBDIRECTORIES)
    list(APPEND allowed_directories ${CMAKE_CURRENT_SOURCE_DIR})

    foreach(item ${allowed_subdirectories})
         cmake_path(
                APPEND CMAKE_CURRENT_SOURCE_DIR
                ${item}
                OUTPUT_VARIABLE directory)
        list(APPEND allowed_directories ${directory})
    endforeach()

    foreach(allowed_filename ${allowed_filenames})
        foreach(directory ${allowed_directories})
            cmake_path(
                APPEND directory
                ${allowed_filename}
                OUTPUT_VARIABLE filename)

            foreach(file_extension ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS})
                cmake_path(
                    REPLACE_EXTENSION filename ${file_extension}
                    OUTPUT_VARIABLE filename)

                if(EXISTS ${filename})
                    list(APPEND filenames ${filename})
                    break()
                endif()
            endforeach()
        endforeach()
    endforeach()

    workspace_helpers_get_parse_arguments_value(
        disallowed_filename_patterns
        ${prefix}
        DISALLOWED_FILENAME_PATTERNS)

    workspace_helpers_get_parse_arguments_value(
        disallowed_filenames
        ${prefix}
        DISALLOWED_FILENAMES)

    foreach(filename ${disallowed_filenames})
        string(JOIN "|" extension_pattern ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS})
        string(REGEX REPLACE "[+]" "[+]" extension_pattern "${extension_pattern}")
        set(file_pattern "${filename}[.](${extension_pattern})$")
        list(APPEND disallowed_filename_patterns "${file_pattern}")
    endforeach()

    foreach(pattern ${disallowed_filename_patterns})
        list(FILTER filenames EXCLUDE REGEX ${pattern})
    endforeach()

    if(DEFINED ${output_variable})
        list(APPEND filenames ${${output_variable}})
    endif()

    set(${output_variable} ${filenames} PARENT_SCOPE)
endfunction()

function(workspace_helpers_set_target_link_libraries name)
    set(list_types INTERFACE PUBLIC PRIVATE)
    set(list_type PRIVATE)
    workspace_helpers_get_parse_arguments_value(items ${name} LINK_LIBRARIES)
    foreach(item ${items})
      list(FIND list_types ${item} index)
      if(index GREATER -1 AND NOT item STREQUAL ${list_type})
        set(list_type ${item})
        continue()
      endif()
      target_link_libraries(${name} ${list_type} ${item})
    endforeach()
endfunction()

function(library_target name)
    workspace_helpers_parse_arguments(${ARGV})
    workspace_helpers_target_type(${name} type)
    workspace_helpers_get_parse_arguments_value(sources ${name} SOURCES)
    workspace_helpers_resolve_target_sources(
        ${name}
        ALLOWED_SUBDIRECTORIES
            src
        ALLOWED_FILENAMES
            DllMain
        DISALLOWED_FILENAME_PATTERNS
            "${name}${WORKSPACE_TEST_SUFFIX_REGEX}"
        OUTPUT_VARIABLE sources
    )
    add_library(${name} ${type} ${sources})
    add_library(${CMAKE_PROJECT_NAME}::${name} ALIAS ${name})

    set(CURRENT_TARGET ${name} PARENT_SCOPE)
    if(BUILD_SHARED_LIBS OR type STREQUAL "SHARED")
        string(TOUPPER "${name}_exports" define_symbol)
        set_target_properties(
            ${name}
            PROPERTIES
            DEFINE_SYMBOL ${define_symbol}
        )

        string(TOUPPER "${name}_BUILD_SHARED_LIBRARY" build_shared)
        target_compile_definitions(
            ${name}
            PUBLIC
            ${build_shared}
        )
    endif()

    workspace_helpers_set_target_properties(${name})
    string(TOUPPER ${name}_ prefix_name)
    target_cmake_binary_include_path(
        export_filename
        ${name}
        export-macros.h
    )
    generate_export_header(
        ${name}
        BASE_NAME ""
        PREFIX_NAME ${prefix_name}
        INCLUDE_GUARD_NAME ${prefix_name}EXPORT_MACROS_H
        DEPRECATED_MACRO_NAME DEPRECATED
        EXPORT_FILE_NAME ${export_filename}
        EXPORT_MACRO_NAME EXPORT
        NO_EXPORT_MACRO_NAME NO_EXPORT
        STATIC_DEFINE STATIC
    )

    workspace_helpers_set_target_link_libraries(${name})
endfunction()


function(executable_target name)
  workspace_helpers_parse_arguments(${ARGV})
  workspace_helpers_get_parse_arguments_value(sources ${name} SOURCES)
  workspace_helpers_target_type(${name} type)

  workspace_helpers_resolve_target_sources(
      ${name}
      ALLOWED_SUBDIRECTORIES
          src
      ALLOWED_FILENAMES
          main
      OUTPUT_VARIABLE sources
  )

  add_executable(${name} ${type} ${sources})
  set(CURRENT_TARGET ${name} PARENT_SCOPE)

  workspace_helpers_set_target_properties(${name})
  workspace_helpers_set_target_link_libraries(${name})
endfunction()


function(test_target name)
    if(NOT BUILD_TESTING)
        return()
    endif()

    string(REGEX MATCH ${WORKSPACE_TEST_SUFFIX_REGEX} test_suffix ${name})
    set(target_name ${name})
    if(NOT test_suffix)
        set(target_name ${name}Tests)
    endif()

    workspace_helpers_parse_arguments(${target_name} ${ARGN})

    workspace_helpers_target_type(${target_name} type)
    workspace_helpers_get_parse_arguments_value(sources ${target_name} SOURCES)

    workspace_helpers_resolve_target_sources(
        ${name}
        ALLOWED_FILENAMES
          main
        ALLOWED_SUBDIRECTORIES
          test
          tests
        DISALLOWED_FILENAMES
          ${disallowed_filenames}
        OUTPUT_VARIABLE sources
    )

    add_executable(${target_name} ${type} ${sources})
    set(CURRENT_TARGET ${target_name} PARENT_SCOPE)

    target_include_directories(${target_name}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test>
    )
    workspace_helpers_set_target_cxx_properties(${target_name})
    workspace_helpers_set_target_output_directory_properties(${target_name})
    workspace_helpers_set_target_pdb_properties(${target_name})

    workspace_helpers_get_parse_arguments_value(props ${target_name} PROPERTIES)
    if(DEFINED props)
        set_target_properties(${target_name} PROPERTIES ${props})
    endif()

    workspace_helpers_set_target_link_libraries(${target_name})

    target_link_libraries(
        ${target_name}
        PRIVATE
        GTest::gtest
        GTest::gmock
    )

    gtest_discover_tests(${target_name})
endfunction()


function(add_sources)
    set(flags)
    set(args TARGET)
    set(list_args)

    make_cmake_variable_name(
        OUTPUT_VARIABLE
        prefix
        add_sources)
    cmake_parse_arguments(
        PARSE_ARGV
        0
        ${prefix}
        "${flags}"
        "${args}"
        "${list_args}"
    )
    workspace_helpers_get_parse_arguments_value(target ${prefix} TARGET)
    if(NOT DEFINED target)
        set(target ${CURRENT_TARGET})
    endif()

    list(FIND ARGV TARGET index)
    if(index GREATER_EQUAL 0)
        list(REMOVE_AT ARGV ${index})
        math(EXPR index "${index} + 1")
        list(REMOVE_AT ARGV ${index})
    endif()

    target_sources(${target} ${ARGV})
endfunction()


function(configure_target_file)
    set(target ${ARGV0})
    if(NOT DEFINED target)
        set(target ${CURRENT_TARGET})
    endif()
    string(JOIN "_" os TARGET OS ${TARGET_OS})
    string(MAKE_C_IDENTIFIER ${os} os)
    string(TOUPPER "${os}" os)
    set(${os} 1)

    string(JOIN "_" INCLUDE_GUARD_NAME ${target} targets h)
    string(MAKE_C_IDENTIFIER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)
    string(TOUPPER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)
    cmake_path(
        APPEND
        CMAKE_CURRENT_FUNCTION_LIST_DIR
        config
        headers
        targets.in
        OUTPUT_VARIABLE input
    )
    target_cmake_binary_include_path(
        output
        ${target}
        targets.h
    )
    configure_file(${input} ${output})
endfunction()

function(setup_msvc)
  if(NOT WIN32)
    return()
  endif()
  
  message("Restoring nuget packages")
  cmake_path(
    APPEND
    CMAKE_CURRENT_FUNCTION_LIST_DIR
    config
    packages.config
    OUTPUT_VARIABLE input
  )
  if(NOT DEFINED NUGET_PACKAGES_DIR)
  cmake_path(
      APPEND
      CMAKE_BINARY_DIR
      packages
      OUTPUT_VARIABLE dir
  )
  
  set(NUGET_PACKAGES_DIR ${dir} CACHE STRING "Nuget package directory")
  endif()
  configure_file(${input} ${NUGET_PACKAGES_DIR}.config COPYONLY)
 
  execute_process(
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND nuget
    restore
    -PackagesDirectory 
    ${NUGET_PACKAGES_DIR}
  )

  cmake_path(
    APPEND
    NUGET_PACKAGES_DIR
    Microsoft.Windows.CppWinRT.2.0.220325.3
    OUTPUT_VARIABLE NUGET_MICROSOFT_WINDOWS_CPPWINRT
  )
  cmake_path(
    APPEND
    NUGET_MICROSOFT_WINDOWS_CPPWINRT
    build
    native
    Microsoft.Windows.CppWinRT.targets
    OUTPUT_VARIABLE cppwinrt_targets
  )
  cmake_path(
    APPEND
    NUGET_MICROSOFT_WINDOWS_CPPWINRT
    build
    native
    Microsoft.Windows.CppWinRT.props
    OUTPUT_VARIABLE cppwinrt_props
  )
  cmake_path(
    APPEND
    NUGET_MICROSOFT_WINDOWS_CPPWINRT
    bin
    cppwinrt.exe
    OUTPUT_VARIABLE cppwinrt_exe
  )
  string(JOIN ";" project_imports ${cppwnrt_props} ${cppwnrt_targets})
  set(NUGET_MICROSOFT_WINDOWS_CPPWINRT_IMPORTS ${project_imports} PARENT_SCOPE)

  set(NUGET_MICROSOFT_WINDOWS_CPPWINRT  ${NUGET_MICROSOFT_WINDOWS_CPPWINRT} PARENT_SCOPE)
  set(CPPWINRT_EXECUTABLE_PATH ${cppwinrt_exe})
  generate_winrt_sdk_projection(OPTIMIZE)
  message("Nuget packages restored")
endfunction()

function(generate_winrt_sdk_projection)
    set(OPTIONS OPTIMIZE)
    set(ONE_VALUE_KEYWORDS EXECUTABLE_PATH PCH_NAME)
    set(MULTI_VALUE_KEYWORDS INPUT)

    cmake_parse_arguments(PARSE_ARGV 0 CPPWINRT "${OPTIONS}" "${ONE_VALUE_KEYWORDS}" "${MULTI_VALUE_KEYWORDS}")

    if(NOT CPPWINRT_PROJECTION_ROOT_PATH)
          cmake_path(
            APPEND
            CMAKE_BINARY_DIR
            generated
            OUTPUT_VARIABLE CPPWINRT_PROJECTION_ROOT_PATH)
    endif()

    if(NOT EXISTS "${CPPWINRT_PROJECTION_ROOT_PATH}/winrt")
        if(NOT CPPWINRT_EXECUTABLE_PATH)
            set(CPPWINRT_EXECUTABLE_PATH ${NUGET_MICROSOFT_WINDOWS_CPPWINRT}/bin/cppwinrt.exe)
        endif()

        set(CPPWINRT_COMMAND ${CPPWINRT_EXECUTABLE_PATH})

        list(APPEND CPPWINRT_COMMAND -output ${CPPWINRT_PROJECTION_ROOT_PATH})
        list(APPEND CPPWINRT_COMMAND -reference sdk)

        if(CPPWINRT_PCH_NAME)
            list(APPEND CPPWINRT_COMMAND -pch ${CPPWINRT_PCH_NAME})
        endif()

        if(CPPWINRT_OPTIMIZE)
            list(APPEND CPPWINRT_COMMAND -optimize)
        endif()

        message(VERBOSE "Generating CppWinRT headers")
        message(VERBOSE "generate_winrt_projection: CPPWINRT_COMMAND = ${CPPWINRT_COMMAND}")

        execute_process(
            COMMAND ${CPPWINRT_COMMAND}
            OUTPUT_VARIABLE CPPWINRT_OUTPUT
            )

        message(VERBOSE "generate_winrt_projection: CPPWINRT_OUTPUT = ${CPPWINRT_OUTPUT}")
    endif()
endfunction()