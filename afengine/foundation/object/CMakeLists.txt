add_sources(
  PUBLIC
  ObjectId.h
  ObjectIdTraits.h
  constants.h
  object.h
)

string(TOLOWER ${TARGET_OS} directory)
add_subdirectory(${directory})
