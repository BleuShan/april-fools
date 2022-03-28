#include <AFEngine/Foundation/Runtime/Runtime.h>
#include <winrt/base.h>

using AFEngine::Foundation::Runtime;

auto Runtime::create() -> Runtime* {
  winrt::init_apartment();
  return new Runtime();
}

auto Runtime::teardown(Runtime* runtime) -> void {
  runtime->shutdown();
  winrt::uninit_apartment();
}