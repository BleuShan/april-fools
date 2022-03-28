#ifndef AFENGINE_FOUNDATION_RUNTIME_H
#define AFENGINE_FOUNDATION_RUNTIME_H

#include <afengine/export_macros.h>

namespace afengine::foundation {
/**
 * The runtime environment
 */
class AFENGINE_API Runtime final {
 public:
  static auto get() -> Runtime&;
  AFENGINE_PRIVATE static auto create() -> Runtime*;
  AFENGINE_PRIVATE static auto teardown(Runtime*) -> void;

  auto shutdown() -> Runtime&;

 private:
  Runtime() = default;
};

}  // namespace afengine::foundation

#endif
