#include <afengine/Foundation/Runtime/Runtime.h>
#include <folly/Singleton.h>

using afengine::foundation::Runtime;
using folly::Singleton;

static auto DefaultRuntime =
    Singleton<Runtime>{Runtime::create, Runtime::teardown}.shouldEagerInit();

Runtime& Runtime::get() {
  return *DefaultRuntime.get();
}

Runtime& Runtime::shutdown() {
  return *this;
}
