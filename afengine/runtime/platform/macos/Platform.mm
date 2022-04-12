#include "Platform.h"
#include "AFEngineApplication.h"
#include "AFEngineApplicationDelegate.h"

namespace afengine::runtime::platform::macos {

auto Platform::platformInitialize() -> void {}

auto Platform::platformRun() -> int {
  @autoreleasepool {
    auto app = AFEngineApplication.sharedApplication;
    auto appDelegate = [[AFEngineApplicationDelegate alloc] init];
    app.delegate = appDelegate;
    [app run];
  }
  return 0;
}

auto Platform::platformShutdown() -> void {
  auto app = AFEngineApplication.sharedApplication;
  if (app.running) {
    [app terminate:app.delegate];
  }
}

auto Platform::platformProcessInfo() const -> core::ProcessInfo {
  @autoreleasepool {
    auto info = [NSProcessInfo processInfo];
    auto argv = [info arguments];
    std::vector<foundation::StdString> args {};
    auto count = [argv count];
    for (int i = 0; i < count; ++i) {
      auto item = argv[i];
      if (item == nil) continue;
      args.emplace_back([item cStringUsingEncoding:NSUTF8StringEncoding]);
    }

    return {
      .processName{[[info processName] cStringUsingEncoding: NSUTF8StringEncoding]},
          .commandLineArguments{std::move(args)}
    };
  }
}

}