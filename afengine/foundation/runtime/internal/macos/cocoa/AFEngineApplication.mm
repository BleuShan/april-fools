#import "AFEngineApplication.h"
#import "AFEngineApplicationDelegate.h"

@interface AFEngineApplication ()
@property(readonly, strong) NSWindow* defaultMainWindow;
@end

@implementation AFEngineApplication {
  NSWindow* defaultMainWindow_;
}

- (instancetype)init {
  self = [super init];
  if (self) {
    self.activationPolicy = NSApplicationActivationPolicyRegular;
    self.delegate = [[AFEngineApplicationDelegate alloc] init];
  }
  return self;
}

- (NSWindow*)mainWindow {
  auto window = [super mainWindow];
  if (window != nil) {
    return window;
  }

  return self.defaultMainWindow;
}

- (NSWindow*)defaultMainWindow {
  if (defaultMainWindow_ == nil) {
    defaultMainWindow_ =
        [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, 640, 480)
                                    styleMask:NSWindowStyleMaskTitled |
                                              NSWindowStyleMaskMiniaturizable |
                                              NSWindowStyleMaskResizable |
                                              NSWindowStyleMaskClosable
                                      backing:NSBackingStoreBuffered
                                        defer:NO];
    auto appName = [[NSProcessInfo processInfo] processName];
    [defaultMainWindow_ setTitle:appName];
    auto appMenu = [[NSMenu alloc] initWithTitle:appName];
    [appMenu addItemWithTitle:[@"Quit " stringByAppendingString:appName]
                       action:@selector(terminate:)
                keyEquivalent:@"q"];
    defaultMainWindow_.menu = [[NSMenu alloc] init];
    auto appMenuItem = [[NSMenuItem alloc] init];
    [appMenuItem setSubmenu:appMenu];
    [defaultMainWindow_.menu addItem:appMenuItem];
    [defaultMainWindow_ makeMainWindow];
  }

  return defaultMainWindow_;
}

@end
