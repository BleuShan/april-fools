#include "Platform.h"
#include "AFEngineApplication.h"
#include "AFEngineApplicationDelegate.h"

#include "../../runtime/Runtime.h"

namespace afengine::runtime::platform::macos {
auto Platform::Initialize() -> void {}

auto Platform::Main() -> int {
  @autoreleasepool {
    auto app = AFEngineApplication.sharedApplication;
    auto appDelegate = [[[AFEngineApplicationDelegate alloc]
        initWithPlatform:this] autorelease];
    app.delegate = appDelegate;
    IsRunning(true);
    [app run];
    IsRunning(false);
  }
  return 0;
}

auto Platform::Terminate(bool notify) -> void {
  if (!IsRunning(false)) return;

  if (notify) {
    auto instance = Runtime::Instance();
    if (instance == nullptr) return;
    instance->Shutdown();
    return;
  };

  auto app = AFEngineApplication.sharedApplication;
  if (app.running) {
    [app terminate:app.delegate];
  }
}

auto Platform::GetCommandLineArguments() const
    -> std::vector<foundation::StringView> {
  std::vector<foundation::StringView> args{};
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