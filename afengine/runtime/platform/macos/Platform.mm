#include "Platform.h"
#include "AFEngineApplication.h"
#include "AFEngineApplicationDelegate.h"

#include "../../runtime/Runtime.h"

namespace afengine::runtime::platform::macos {

auto Platform::PlatformBootstrap() -> void {}

auto Platform::Run() -> int {
  @autoreleasepool {
    auto app = AFEngineApplication.sharedApplication;
    auto appDelegate =
        [[AFEngineApplicationDelegate alloc] initWithPlatform:this];
    app.delegate = appDelegate;
    IsRunning(true);
    [app run];
    IsRunning(false);
  }
  return 0;
}

auto Platform::PlatformShutdown() -> void {
  auto app = AFEngineApplication.sharedApplication;
  if (app.running) {
    [app terminate:app.delegate];
  }
}

auto Platform::PlatformCommandlineArguments() const
    -> std::vector<foundation::StdStringView> {
  std::vector<foundation::StdStringView> args{};
  auto argv = [[NSProcessInfo processInfo] arguments];
  auto count = [argv count];
  for (int i = 0; i < count; ++i) {
    auto item = argv[i];
    if (item == nil) continue;
    args.emplace_back([item cStringUsingEncoding:NSUTF8StringEncoding]);
  }

  return args;
}

}