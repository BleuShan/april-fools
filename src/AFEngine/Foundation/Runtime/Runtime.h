#ifndef AFENGINE_FOUNDATION_RUNTIME_H
#define AFENGINE_FOUNDATION_RUNTIME_H

#include <AFEngine/export_macros.h>

namespace AFEngine::Foundation {
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

}  // namespace AFEngine::Foundation

#endif
