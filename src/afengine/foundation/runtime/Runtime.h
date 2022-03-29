#ifndef AFENGINE_FOUNDATION_RUNTIME_H
#define AFENGINE_FOUNDATION_RUNTIME_H

#include <afengine/export_macros.h>

#include <functional>

namespace afengine::foundation {
/**
 * The runtime environment
 */
class AFENGINE_API Runtime final {
 public:
  using AcquireCallback = std::function<void(Runtime&)>;
  static auto acquire(AcquireCallback callback) -> bool;
  AFENGINE_PRIVATE static auto create() -> Runtime*;
  AFENGINE_PRIVATE static auto teardown(Runtime*) -> void;

  auto shutdown() -> Runtime&;

 private:
  Runtime() = default;
};

}  // namespace afengine::foundation

#endif
