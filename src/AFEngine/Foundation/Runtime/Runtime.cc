#include <AFEngine/Foundation/Runtime/Runtime.h>
#include <folly/Singleton.h>

using AFEngine::Foundation::Runtime;
using folly::Singleton;

static auto DefaultRuntime =
    Singleton<Runtime>{Runtime::create, Runtime::teardown}.shouldEagerInit();

auto Runtime::get() -> Runtime& {
  return *DefaultRuntime.get();
}

auto Runtime::shutdown() -> Runtime& {
  return *this;
}
