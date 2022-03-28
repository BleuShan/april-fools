#include <afengine/Foundation/Runtime/Runtime.h>
#include <winrt/base.h>

using afengine::foundation::Runtime;

Runtime* Runtime::create() {
  winrt::init_apartment();
  return new Runtime();
}

void Runtime::teardown(Runtime* runtime) {
  runtime->shutdown();
  winrt::uninit_apartment();
}
