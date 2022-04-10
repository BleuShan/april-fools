#ifndef AFENGINE_RUNTIME_RUNTIME_RUNTIME_H
#define AFENGINE_RUNTIME_RUNTIME_RUNTIME_H

#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime {

namespace platform::core {
class Platform;
}

/**
 * The runtime environment
 */
class AFENGINE_EXPORT Runtime final {
  public:
    static auto Instance() -> Runtime*;

    auto Run() const -> int;
    auto Shutdown() -> Runtime&;

    [[nodiscard]] auto Platform() const -> platform::core::Platform&;

  private:
    friend auto MakeDefaultRuntime() -> gsl::owner<Runtime*>;
    std::unique_ptr<platform::core::Platform> platform_{nullptr};

    explicit Runtime(decltype(platform_)::pointer platform) noexcept
      : platform_{platform} {
    }

    explicit Runtime(decltype(platform_)&& platform) noexcept
      : platform_{std::move(platform)} {
    }

    auto Bootstrap() const -> void;
};

} // namespace afengine::runtime

#endif
