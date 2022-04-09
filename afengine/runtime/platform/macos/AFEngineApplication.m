#import "AFEngineApplication.h"

@implementation AFEngineApplication {
  NSWindow* defaultMainWindow_;
}

- (instancetype)init {
  self = [super init];
  if (self) {
    self.activationPolicy = NSApplicationActivationPolicyRegular;
  }
  return self;
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
    id appName = [[NSProcessInfo processInfo] processName];
    [defaultMainWindow_ setTitle:appName];
    id appMenu = [[NSMenu alloc] initWithTitle:appName];
    [appMenu addItemWithTitle:[@"Quit " stringByAppendingString:appName]
                       action:@selector(terminate:)
                keyEquivalent:@"q"];
    defaultMainWindow_.menu = [[NSMenu alloc] init];
    id appMenuItem = [[NSMenuItem alloc] init];
    [appMenuItem setSubmenu:appMenu];
    [defaultMainWindow_.menu addItem:appMenuItem];
  }

  return defaultMainWindow_;
}

@end
