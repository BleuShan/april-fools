#include "Runtime.h"

#include <folly/Singleton.h>
#include <glog/logging.h>

#include "../platform/platform.h"

using afengine::runtime::Runtime;
using RuntimeSingleton = folly::Singleton<Runtime>;

namespace afengine::runtime {

auto Runtime::Instance() -> Runtime* {
  const auto instance = RuntimeSingleton::try_get();
  if (instance == nullptr) {
    return nullptr;
  }
  return instance.get();
}

auto Runtime::Bootstrap() const -> void {
  Platform().Bootstrap();
  const auto args = Platform().CommandlineArguments();
  google::InitGoogleLogging(args[0].data());

}


auto Runtime::Run() const -> int {
  return Platform().Run();
}

auto Runtime::Shutdown() -> Runtime& {
  Platform().Shutdown();
  google::ShutdownGoogleLogging();
  platform_ = nullptr;
  return *this;
}

auto Runtime::Platform() const -> platform::core::Platform& {
  if (platform_ == nullptr) {
    throw std::domain_error("Runtime shutdown");
  }

  return *platform_;
}

auto MakeDefaultRuntime() -> gsl::owner<Runtime*> {
  auto instance = new Runtime{std::make_unique<platform::DefaultPlatform>()};
  instance->Bootstrap();
  return instance;
}

auto TeardownRuntime(Runtime* instance) -> void {
  instance->Shutdown();
}

} // namespace afengine::runtime

namespace {
using afengine::runtime::MakeDefaultRuntime;
using afengine::runtime::TeardownRuntime;

[[maybe_unused]] const RuntimeSingleton kDefaultRuntime{
    MakeDefaultRuntime,
    TeardownRuntime}; // namespace
}                     // namespace
