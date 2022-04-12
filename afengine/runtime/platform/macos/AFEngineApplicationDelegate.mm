#import "AFEngineApplicationDelegate.h"
#import "../../runtime/Runtime.h"
#import "AFEngineWindow.h"

using afengine::runtime::Runtime;

@implementation AFEngineApplicationDelegate {
  __strong AFEngineWindow* _window;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
  _window = [AFEngineWindow defaultWindow];
  [_window displayIfNeeded];
  [_window orderFrontRegardless];
  [_window makeMainWindow];
}

- (void)applicationWillTerminate:(NSNotification*)notification {
  Runtime::instance().shutdown();
}

@end