include_guard()

function(list_contains list value variable)
  LIST(FIND "${list}" "${value}" index)

  if (${index} GREATER_EQUAL 0)
    set(${variable} ON PARENT_SCOPE)
  else ()
    set(${variable} OFF PARENT_SCOPE)
  endif ()
endfunction()

function(make_cmake_variable_name)
  unset(varname)
  set(keywords OUTPUT_VARIABLE)
  foreach (value IN LISTS ARGV)
    list_contains(keywords "${value}" is_keyword)
    if (DEFINED keyword)
      if (keyword STREQUAL OUTPUT_VARIABLE AND NOT DEFINED varname)
        set(varname ${value})
        list(FILTER keywords EXCLUDE REGEX "^${keyword}$")
        unset(keyword)
        continue()
      endif ()
    endif ()

    if (is_keyword AND NOT DEFINED keyword)
      set(keyword ${value})
      continue()
    endif ()

    list(APPEND input ${value})
  endforeach ()

  if (NOT DEFINED varname OR varname STREQUAL "")
    string(JOIN " " argv_string ${ARGV})
    message(FATAL_ERROR "invalid arguments: ${argv_string}")
  endif ()

  string(JOIN "_" varvalue ${input})
  string(TOUPPER ${varvalue} varvalue)
  set(${varname} ${varvalue} PARENT_SCOPE)
endfunction()

function(make_cmake_binary_path variable)
  cmake_path(
    APPEND
    CMAKE_BINARY_DIR
    ${ARGN}
    OUTPUT_VARIABLE value
  )
  string(TOLOWER ${value} value)
  set(${variable} ${value} PARENT_SCOPE)
endfunction()
