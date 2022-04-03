#include <afengine/foundation/Runtime/Runtime.h>
#include <winrt/base.h>

using afengine::foundation::Runtime;

auto Runtime::Create() -> Runtime* {
  winrt::init_apartment();
  return new Runtime();
}

auto Runtime::Teardown(Runtime* runtime) -> void {
  runtime->Shutdown();
  winrt::uninit_apartment();
}
