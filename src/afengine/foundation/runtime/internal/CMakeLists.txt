add_sources(
  PUBLIC
  internal.h
)

string(TOLOWER ${TARGET_OS} directory)
add_subdirectory(${directory})
