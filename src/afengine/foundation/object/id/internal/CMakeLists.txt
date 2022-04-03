add_sources(
  PUBLIC
  ObjectIdTrait.h
  internal.h
)

string(TOLOWER ${TARGET_OS} directory)
add_subdirectory(${directory})
