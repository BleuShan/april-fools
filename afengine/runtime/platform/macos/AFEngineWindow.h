#ifndef AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEWINDOW_H
#define AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEWINDOW_H

#ifdef __OBJC__
  #include <AppKit/AppKit.h>

@interface AFEngineWindow : NSWindow
+ (instancetype)defaultWindow;
@end

#endif

#endif  // AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEWINDOW_H
