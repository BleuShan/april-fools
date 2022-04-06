#include "Runtime.h"

using afengine::foundation::Runtime;
using afengine::foundation::internal::DefaultRuntimeSingletonTag;
using folly::Singleton;

[[maybe_unused]] const auto kDefaultRuntime =
    Singleton<Runtime, DefaultRuntimeSingletonTag, DefaultRuntimeSingletonTag>{
        Runtime::Create, Runtime::Teardown}
        .shouldEagerInit();

auto Runtime::Shutdown() -> Runtime& {
  return *this;
}
