#ifndef AFENGINE_RUNTIME_RUNTIME_RUNTIME_H
#define AFENGINE_RUNTIME_RUNTIME_RUNTIME_H

#include <folly/Singleton.h>

#include "../platform/core/core.h"
#include "afengine/foundation/memory/memory.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime {
/**
 * The runtime environment
 */
class AFENGINE_EXPORT Runtime final {
  public:
    static auto Instance() -> Runtime*;

    auto Start() -> int;
    auto Shutdown() -> Runtime&;

    [[nodiscard]] inline auto Platform() const noexcept
        -> platform::core::Platform* {
      return platform_.get();
    }

  private:
    friend auto MakeDefaultRuntime() -> gsl::owner<Runtime*>;
    Runtime();
    std::unique_ptr<platform::core::Platform> platform_{nullptr};
};

}  // namespace afengine::runtime

#endif
