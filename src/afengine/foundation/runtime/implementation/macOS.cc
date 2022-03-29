#include <afengine/foundation/runtime/Runtime.h>

using afengine::foundation::Runtime;

Runtime* Runtime::create() {
  return new Runtime();
}

void Runtime::teardown(Runtime* runtime) {
  runtime->shutdown();
}
