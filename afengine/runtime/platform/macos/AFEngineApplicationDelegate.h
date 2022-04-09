#ifndef AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEAPPLICATIONDELEGATE_H
#define AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEAPPLICATIONDELEGATE_H

#ifdef __OBJC__
  #include <AppKit/AppKit.h>

  #include "Platform.h"

@interface AFEngineApplicationDelegate : NSResponder <NSApplicationDelegate>
- (instancetype)initWithPlatform:
    (afengine::runtime::platform::macos::Platform*)platform;
@end

#endif

#endif  // AFENGINE_FOUNDATION_RUNTIME_INTERNAL_MACOS_COCOA_AFENGINEAPPLICATIONDELEGATE_H
