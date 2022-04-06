include_guard()
include(WorkspaceUtilities)
include(GenerateExportHeader)


function(generate_target_files)
  set(flags LIBRARY)
  set(args TARGET)
  set(list_args)

  cmake_parse_arguments(
    PARSE_ARGV 0
    ARGV
    "${flags}"
    "${args}"
    "${list_args}"
  )

  if (NOT DEFINED ARGV_TARGET)
    set(ARGV_TARGET ${CURRENT_TARGET})
  endif ()

  cmake_path(
    APPEND
    CMAKE_CURRENT_FUNCTION_LIST_DIR
    templates
    OUTPUT_VARIABLE template_path
  )

  make_cmake_binary_path(
    generated_include
    generated
    include
  )

  cmake_path(
    APPEND
    generated_include
    ${ARGV_TARGET}
    OUTPUT_VARIABLE base_path
  )

  if (ARGV_LIBRARY)
    string(TOUPPER ${ARGV_TARGET}_ prefix_name)
    make_cmake_binary_path(
      export_filename
      ${base_path}
      macros
      exports.h
    )
    cmake_path(RELATIVE_PATH export_filename BASE_DIRECTORY ${generated_include} OUTPUT_VARIABLE INCLUDE_GUARD_NAME)
    string(MAKE_C_IDENTIFIER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)
    string(TOUPPER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)
    generate_export_header(
      ${ARGV_TARGET}
      BASE_NAME ""
      PREFIX_NAME ${prefix_name}
      INCLUDE_GUARD_NAME ${INCLUDE_GUARD_NAME}
      DEPRECATED_MACRO_NAME DEPRECATED
      EXPORT_FILE_NAME ${export_filename}
      EXPORT_MACRO_NAME EXPORT
      NO_EXPORT_MACRO_NAME NO_EXPORT
      STATIC_DEFINE STATIC
    )
  endif ()

  string(JOIN "_" os TARGET OS ${TARGET_OS})
  string(MAKE_C_IDENTIFIER ${os} os)
  string(TOUPPER "${os}" os)
  set(${os} 1)

  cmake_path(
    APPEND
    CMAKE_CURRENT_FUNCTION_LIST_DIR
    templates
    OUTPUT_VARIABLE template_base
  )
  cmake_path(
    APPEND
    template_base
    **
    *.h.in
    OUTPUT_VARIABLE glob
  )
  file(GLOB_RECURSE inputs ${glob})
  foreach (input IN LISTS inputs)
    cmake_path(RELATIVE_PATH input BASE_DIRECTORY ${template_base} OUTPUT_VARIABLE file)
    cmake_path(REMOVE_EXTENSION file LAST_ONLY OUTPUT_VARIABLE output)
    cmake_path(
      APPEND
      base_path
      ${output}
      OUTPUT_VARIABLE output
    )
    cmake_path(RELATIVE_PATH output BASE_DIRECTORY ${generated_include} OUTPUT_VARIABLE INCLUDE_GUARD_NAME)
    string(MAKE_C_IDENTIFIER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)
    string(TOUPPER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)
    configure_file(${input} ${output})
  endforeach ()
endfunction()


function(generate_winrt_sdk_projection)
  set(OPTIONS OPTIMIZE)
  set(ONE_VALUE_KEYWORDS EXECUTABLE_PATH PCH_NAME)
  set(MULTI_VALUE_KEYWORDS INPUT)

  cmake_parse_arguments(PARSE_ARGV 0 CPPWINRT "${OPTIONS}" "${ONE_VALUE_KEYWORDS}" "${MULTI_VALUE_KEYWORDS}")

  if (NOT CPPWINRT_PROJECTION_ROOT_PATH)
    cmake_path(
      APPEND
      CMAKE_BINARY_DIR
      generated
      OUTPUT_VARIABLE CPPWINRT_PROJECTION_ROOT_PATH)
  endif ()

  if (NOT EXISTS "${CPPWINRT_PROJECTION_ROOT_PATH}/winrt")
    if (NOT CPPWINRT_EXECUTABLE_PATH)
      set(CPPWINRT_EXECUTABLE_PATH ${NUGET_MICROSOFT_WINDOWS_CPPWINRT}/bin/cppwinrt.exe)
    endif ()

    set(CPPWINRT_COMMAND ${CPPWINRT_EXECUTABLE_PATH})

    list(APPEND CPPWINRT_COMMAND -output ${CPPWINRT_PROJECTION_ROOT_PATH})
    list(APPEND CPPWINRT_COMMAND -reference sdk)

    if (CPPWINRT_PCH_NAME)
      list(APPEND CPPWINRT_COMMAND -pch ${CPPWINRT_PCH_NAME})
    endif ()

    if (CPPWINRT_OPTIMIZE)
      list(APPEND CPPWINRT_COMMAND -optimize)
    endif ()

    message(VERBOSE "Generating CppWinRT headers")
    message(VERBOSE "generate_winrt_projection: CPPWINRT_COMMAND = ${CPPWINRT_COMMAND}")

    execute_process(
      COMMAND ${CPPWINRT_COMMAND}
      OUTPUT_VARIABLE CPPWINRT_OUTPUT
    )

    message(VERBOSE "generate_winrt_projection: CPPWINRT_OUTPUT = ${CPPWINRT_OUTPUT}")
  endif ()
endfunction()