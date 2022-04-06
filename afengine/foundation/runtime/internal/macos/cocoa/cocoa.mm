#include "cocoa.h"

#ifdef __cplusplus

namespace afengine::foundation {

auto CocoaMain() -> int {
  @autoreleasepool {
    auto* app = [AFEngineApplication sharedApplication];

    [app run];
  }

  return 0;
}

}

#endif
