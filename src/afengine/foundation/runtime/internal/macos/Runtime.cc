#include <afengine/foundation/runtime/Runtime.h>

using afengine::foundation::Runtime;

auto Runtime::Create() -> Runtime* {
  return new Runtime();
}

auto Runtime::Teardown(Runtime* runtime) -> void {
  runtime->Shutdown();
}
