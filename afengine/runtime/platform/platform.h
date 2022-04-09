#ifndef AFENGINE_RUNTIME_PLATFORM_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_PLATFORM_H

#include "afengine/macros/macros.h"
#include "core/core.h"

#if TARGET_OS_WINDOWS
  #include "windows/Platform.h"
#elif TARGET_OS_MACOS
  #include "macos/Platform.h"
#endif

namespace afengine::runtime::platform {
#if TARGET_OS_WINDOWS
using DefaultPlatform = windows::Platform;
#elif TARGET_OS_MACOS
using DefaultPlatform = macos::Platform;
#endif
}  // namespace afengine::runtime::platform

#endif  // AFENGINE_FOUNDATION_RUNTIME_PLATFORM_PLATFORM_H
