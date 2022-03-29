#include <afengine/foundation/runtime/Runtime.h>
#include <folly/Singleton.h>

using afengine::foundation::Runtime;
using folly::Singleton;

static auto DefaultRuntime =
    Singleton<Runtime>{Runtime::create, Runtime::teardown}.shouldEagerInit();

auto Runtime::acquire(AcquireCallback callback) -> bool {
  auto instance = DefaultRuntime.try_get();
  if (instance == nullptr) {
    return false;
  }

  callback(*instance);

  return true;
}

auto Runtime::shutdown() -> Runtime& {
  return *this;
}
