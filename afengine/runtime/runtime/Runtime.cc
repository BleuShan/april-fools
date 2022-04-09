#include "Runtime.h"

#include <folly/Singleton.h>

#include "../platform/platform.h"
#include "glog/logging.h"

namespace runtime = afengine::runtime;

using runtime::Runtime;
using RuntimeSingleton = folly::Singleton<Runtime>;

[[maybe_unused]] static const RuntimeSingleton kDefaultRuntime{
    []() -> Runtime* {
      return new Runtime();  // NOLINT(cppcoreguidelines-owning-memory)
    },
    [](Runtime* instance) { instance->Shutdown(); }};

namespace afengine::runtime {
Runtime::Runtime() : platform_(std::make_unique<platform::DefaultPlatform>()) {}

auto Runtime::Instance() -> Runtime* {
  auto instance = RuntimeSingleton::try_get();
  if (instance == nullptr) {
    return nullptr;
  }
  return instance.get();
}

auto Runtime::Start() -> int {
  auto args = Platform().CommandlineArguments();
  google::InitGoogleLogging(args[0].data());
  folly::SingletonVault::singleton()->registrationComplete();
  return platform_->Run();
}

auto Runtime::Shutdown() -> Runtime& {
  if (platform_ == nullptr) return *this;

  if (platform_->IsRunning()) {
    platform_->Shutdown();
  }
  platform_ = nullptr;
  google::ShutdownGoogleLogging();
  return *this;
}

}  // namespace afengine::runtime
