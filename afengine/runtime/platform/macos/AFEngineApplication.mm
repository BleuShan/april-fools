#import "AFEngineApplication.h"
#import "AFEngineMenu.h"

@implementation AFEngineApplication

- (instancetype)init {
  self = [super init];
  if (self) {
    self.activationPolicy = NSApplicationActivationPolicyRegular;
    self.mainMenu = [AFEngineMenu defaultAppMenu];
  }
  return self;
}

@end
