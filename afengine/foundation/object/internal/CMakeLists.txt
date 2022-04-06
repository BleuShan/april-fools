add_sources(
  PUBLIC
  BasicObjectId.h
  constants.h
  internal.h
)

string(TOLOWER ${TARGET_OS} directory)
add_subdirectory(${directory})
