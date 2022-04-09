#include <afengine/afengine.h>
#include <folly/Singleton.h>

using afengine::runtime::Runtime;

auto main(int argc, char** argv) -> int {
  auto runtime = Runtime::Instance();

  if (runtime == nullptr) {
    return -1;
  }

  auto result = runtime->Start();

  return result;
}