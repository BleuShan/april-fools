#include "../../Runtime.h"

#include "cocoa/cocoa.h"

using afengine::foundation::Runtime;

auto Runtime::Create() -> Runtime* {
  return new Runtime();
}

auto Runtime::Start() -> int {
  return CocoaMain();
}

auto Runtime::Teardown(Runtime* runtime) -> void {
  runtime->Shutdown();
}