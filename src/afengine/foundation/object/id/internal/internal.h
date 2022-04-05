#ifndef AFENGINE_FOUNDATION_INTERNAL_OBJECTID_H
#define AFENGINE_FOUNDATION_INTERNAL_OBJECTID_H

#include <afengine/foundation/object/id/internal/BasicObjectId.h>
#include <afengine/foundation/object/id/internal/constants.h>
#include <afengine/targets.h>

#if TARGET_OS_WINDOWS
  #include <afengine/foundation/object/id/internal/windows/ObjectId.h>
#elif TARGET_OS_MACOS
  #include <afengine/foundation/object/id/internal/macos/ObjectIdHooks.h>
#endif
#endif
