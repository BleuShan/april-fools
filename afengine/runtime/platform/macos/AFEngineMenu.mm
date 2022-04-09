#include "AFEngineMenu.h"

@implementation AFEngineMenu
+ (instancetype)defaultAppMenu {
  AFEngineMenu* menu = [[AFEngineMenu alloc] init];
  auto appName = [[NSProcessInfo processInfo] processName];
  auto appMenu = [[NSMenu alloc] initWithTitle:appName];
  [appMenu addItemWithTitle:[@"Quit " stringByAppendingString:appName]
                     action:@selector(terminate:)
              keyEquivalent:@"q"];
  auto appMenuItem = [[NSMenuItem alloc] init];
  appMenuItem.submenu = appMenu;
  [menu addItem:appMenuItem];
  return menu;
}
@end