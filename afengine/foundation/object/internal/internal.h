#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_H

#include "BasicObjectId.h"
#include "afengine/macros/macros.h"
#include "constants.h"

#if TARGET_OS_WINDOWS
  #include "windows/ObjectIdHooks.h"
#elif TARGET_OS_MACOS
  #include "macos/ObjectIdHooks.h"
#endif
#endif
