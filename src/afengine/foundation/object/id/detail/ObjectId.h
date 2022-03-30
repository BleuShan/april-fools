#ifndef AFENGINE_FOUNDATION_DETAIL_OBJECTID_H
#define AFENGINE_FOUNDATION_DETAIL_OBJECTID_H

#include <afengine/targets.h>

#if TARGET_OS_WINDOWS
  #include <afengine/foundation/object/id/detail/window/ObjectId.h>
#elif TARGET_OS_MACOS
  #include <afengine/foundation/object/id/detail/macos/ObjectId.h>
#endif

#endif
