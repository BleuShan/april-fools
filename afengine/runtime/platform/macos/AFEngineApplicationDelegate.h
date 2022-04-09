#ifndef AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEAPPLICATIONDELEGATE_H
#define AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEAPPLICATIONDELEGATE_H

#ifdef __OBJC__
  #include <AppKit/AppKit.h>

namespace afengine::runtime::platform::core {
class Platform;
}

@interface AFEngineApplicationDelegate : NSResponder <NSApplicationDelegate>
- (instancetype)initWithPlatform:
    (afengine::runtime::platform::core::Platform*)platform;
@end

#endif

#endif  // AFENGINE_FOUNDATION_RUNTIME_INTERNAL_MACOS_COCOA_AFENGINEAPPLICATIONDELEGATE_H
