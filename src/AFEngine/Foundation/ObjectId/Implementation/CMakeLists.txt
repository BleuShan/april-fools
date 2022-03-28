if(WIN32)
  add_sources(
    PRIVATE
    windows.cc
  )
endif()

if(UNIX)
  add_sources(
    PRIVATE
    unix.cc
  )
endif()