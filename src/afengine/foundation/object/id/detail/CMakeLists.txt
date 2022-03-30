add_sources(
  PUBLIC
  ObjectId.h
)

string(TOLOWER ${TARGET_OS} directory)
add_subdirectory(${directory})
