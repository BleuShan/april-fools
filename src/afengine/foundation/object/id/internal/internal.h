#ifndef AFENGINE_FOUNDATION_OBJECT_ID_INTERNAL_H
#define AFENGINE_FOUNDATION_OBJECT_ID_INTERNAL_H

#include <afengine/foundation/object/id/internal/ObjectIdTrait.h>
#include <afengine/targets.h>

#if TARGET_OS_WINDOWS
  #include <afengine/foundation/object/id/internal/windows/ObjectId.h>
#elif TARGET_OS_MACOS
  #include <afengine/foundation/object/id/internal/macos/ObjectId.h>
#endif
#endif
