#import "AFEngineApplicationDelegate.h"
#import "AFEngineApplication.h"

using afengine::runtime::platform::macos::Platform;

@implementation AFEngineApplicationDelegate {
  Platform* _platform;
}

- (instancetype)initWithPlatform:(Platform*)platform {
  self = [self init];
  if (self) {
    _platform = platform;
  }

  return self;
}

- (void)applicationWillFinishLaunching:(NSNotification*)notification {
  AFEngineApplication* app = [NSApplication sharedApplication];

  auto window = app.defaultMainWindow;
  [window makeKeyAndOrderFront:self];
  [app setMainMenu:window.menu];
}

- (void)applicationWillTerminate:(NSNotification*)notification {
  _platform->NotifyShutdown();
}

@end