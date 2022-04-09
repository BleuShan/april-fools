#ifndef AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEAPPLICATION_H
#define AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEAPPLICATION_H

#ifdef __OBJC__
  #include <AppKit/AppKit.h>

@interface AFEngineApplication : NSApplication
@property(readonly, strong) NSWindow* defaultMainWindow;
@end

#endif

#endif  // AFENGINE_FOUNDATION_RUNTIME_INTERNAL_MACOS_COCOA_AFENGINEAPPLICATION_H
