#import "afengine/foundation/foundation.h"

using afengine::foundation::Runtime;

auto main(int argc, char const* argv[]) -> int {
  auto result =
      Runtime::Acquire<int>([](Runtime& runtime) { return runtime.Start(); });

  if (!result.has_value()) {
    return -1;
  }

  return result.value();
}
