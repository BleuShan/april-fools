#ifndef AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEMENU_H
#define AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEMENU_H

#ifdef __OBJC__
  #include <AppKit/AppKit.h>

@interface AFEngineMenu : NSMenu
+ (instancetype)defaultAppMenu;
@end

#endif
#endif  // AFENGINE_RUNTIME_PLATFORM_MACOS_AFENGINEMENU_H
