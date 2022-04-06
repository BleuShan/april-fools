#include "AFEngineApplicationDelegate.h"
#include "AFEngineApplication.h"

@implementation AFEngineApplicationDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)notification {
  AFEngineApplication* app = [NSApplication sharedApplication];

  auto window = app.mainWindow;
  [window makeKeyAndOrderFront:self];
  [app setMainMenu:window.menu];
}

@end