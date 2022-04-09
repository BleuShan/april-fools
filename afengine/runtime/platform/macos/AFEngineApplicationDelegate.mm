#import "AFEngineApplicationDelegate.h"
#import "../../runtime/Runtime.h"
#import "AFEngineApplication.h"
#import "AFEngineWindow.h"

using afengine::runtime::platform::core::Platform;
using afengine::runtime::Runtime;

@implementation AFEngineApplicationDelegate {
  Platform* _platform;
  __strong AFEngineWindow* _window;
}

- (instancetype)init {
  auto runtime = Runtime::Instance();
  if (runtime == nullptr) {
    return nil;
  }

  auto platform = runtime->Platform();
  self = [self initWithPlatform:platform];
  return self;
}

- (instancetype)initWithPlatform:(Platform*)platform {
  self = [super init];
  if (self) {
    _platform = platform;
  }

  return self;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
  _window = [AFEngineWindow defaultWindow];
  [_window displayIfNeeded];
  [_window orderFrontRegardless];
  [_window makeMainWindow];
}

- (void)applicationWillTerminate:(NSNotification*)notification {
  if (_platform != nil) {
    _platform->NotifyShutdown();
  }
}

@end