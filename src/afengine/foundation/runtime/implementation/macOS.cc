#include <afengine/foundation/runtime/Runtime.h>

using afengine::foundation::Runtime;

auto Runtime::create() -> Runtime* {
  return new Runtime();
}

auto Runtime::teardown(Runtime* runtime) -> void {
  runtime->shutdown();
}
