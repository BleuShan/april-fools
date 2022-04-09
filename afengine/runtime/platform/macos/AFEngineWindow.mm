#include "AFEngineWindow.h"

@implementation AFEngineWindow
static const CGFloat kDefaultWindowWidth = 640.0F;
static const CGFloat kDefaultWindowHeight = 440.0F;
static const CGFloat kDefaultScreenToWindowSizeScaleFactor = 0.5F;

+ (instancetype)defaultWindow {
  NSScreen* mainScreen = [NSScreen mainScreen];
  NSRect rect = [AFEngineWindow getDefaultRect:mainScreen];
  id window = [[AFEngineWindow alloc]
      initWithContentRect:rect
                styleMask:NSWindowStyleMaskTitled |
                          NSWindowStyleMaskMiniaturizable |
                          NSWindowStyleMaskResizable | NSWindowStyleMaskClosable
                  backing:NSBackingStoreBuffered
                    defer:NO
                   screen:mainScreen];

  return [window setDefaults];
}

+ (NSRect)getDefaultRect:(NSScreen* _Nullable)screen {
  if (screen == nil) {
    return NSMakeRect(0, 0, kDefaultWindowWidth, kDefaultWindowHeight);
  }

  NSRect frame = [screen visibleFrame];
  CGFloat height = NSHeight(frame) * kDefaultScreenToWindowSizeScaleFactor;
  CGFloat width = NSWidth(frame) * kDefaultScreenToWindowSizeScaleFactor;
  return NSMakeRect(0, 0, width, height);
}

- (instancetype)setDefaults {
  id appName = [[NSProcessInfo processInfo] processName];
  [self setTitle:appName];

  [self center];
  return self;
}

@end