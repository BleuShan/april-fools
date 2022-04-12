#include "Runtime.h"

#include <glog/logging.h>

namespace afengine::runtime {

auto Runtime::initialize() -> void {
  auto [processName, _exec, _args] = platform().initialize().processInfo();
  google::InitGoogleLogging(processName.c_str());
  status_ = Status::Stopped;
}

auto Runtime::start() -> int {
  if (status_ != Status::Stopped) {
    throw std::invalid_argument("Cannot start runtime in the current state.");
  }

  status_ = Status::Started;
  auto result = platform().run();
  status_ = Status::Stopped;
  return result;
}

auto Runtime::shutdown() -> Runtime& {
  platform().shutdown();
  google::ShutdownGoogleLogging();
  platform_ = nullptr;

  status_ = Status::Shutdown;
  return *this;
}

auto Runtime::platform() const -> platform::core::Platform& {
  if (platform_ == nullptr) {
    throw std::domain_error("Runtime shutdown");
  }

  return *platform_;
}

auto makeDefaultRuntime() -> gsl::owner<Runtime*> {
  auto instance = new Runtime{std::make_unique<platform::DefaultPlatform>()};
  instance->initialize();
  return instance;
}

auto teardownRuntime(Runtime* instance) -> void {
  if (instance->currentStatus() != Runtime::Status::Shutdown) {
    instance->shutdown();
  }
}

}  // namespace afengine::runtime

namespace {

using afengine::runtime::makeDefaultRuntime;
using afengine::runtime::Runtime;
using afengine::runtime::teardownRuntime;

[[maybe_unused]] const Runtime::Holder kDefaultRuntime{
    makeDefaultRuntime, teardownRuntime};  // namespace
}  // namespace
