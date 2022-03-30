#include <afengine/foundation/Runtime/Runtime.h>
#include <winrt/base.h>

using afengine::foundation::Runtime;

auto Runtime::create() -> Runtime* {
  winrt::init_apartment();
  return new Runtime();
}

auto Runtime::teardown(Runtime* runtime) -> void {
  runtime->shutdown();
  winrt::uninit_apartment();
}
