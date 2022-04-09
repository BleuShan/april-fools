#include "Runtime.h"

#include <folly/Singleton.h>

#include "../platform/platform.h"
#include "glog/logging.h"

using afengine::runtime::Runtime;
using RuntimeSingleton = folly::Singleton<Runtime>;

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
  auto args = Platform()->CommandlineArguments();
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

auto MakeDefaultRuntime() -> gsl::owner<Runtime*> {
  return new Runtime();
}

auto TeardownRuntime(Runtime* instance) -> void {
  instance->Shutdown();
}

}  // namespace afengine::runtime

namespace {
using afengine::runtime::MakeDefaultRuntime;
using afengine::runtime::TeardownRuntime;

[[maybe_unused]] static const RuntimeSingleton kDefaultRuntime{
    MakeDefaultRuntime, TeardownRuntime};  // namespace
}  // namespace