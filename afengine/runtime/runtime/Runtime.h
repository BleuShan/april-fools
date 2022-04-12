#ifndef AFENGINE_RUNTIME_RUNTIME_RUNTIME_H
#define AFENGINE_RUNTIME_RUNTIME_RUNTIME_H

#include "../platform/platform.h"
#include "afengine/foundation/traits/Singleton.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime {

/**
 * The runtime environment
 */
class AFENGINE_EXPORT Runtime final : public foundation::Singleton<Runtime> {
  public:
    enum class Status : uint8_t { Initial = 0, Stopped, Started, Shutdown };

    Runtime(const Runtime& source) = delete;
    Runtime(Runtime&& source) noexcept = default;

    auto operator=(Runtime&& source) noexcept -> Runtime& = default;
    auto operator=(const Runtime& source) -> Runtime& = delete;

    [[nodiscard]] auto start() -> int;
    auto shutdown() -> Runtime&;

    [[nodiscard]] auto platform() const -> platform::core::Platform&;
    [[nodiscard]] auto currentStatus() const -> Status { return status_; }

  private:
    friend auto makeDefaultRuntime() -> gsl::owner<Runtime*>;
    std::unique_ptr<platform::core::Platform> platform_{nullptr};
    Status status_{Status::Initial};

    explicit Runtime(decltype(platform_)::pointer platform) noexcept
        : platform_{platform} {}

    explicit Runtime(decltype(platform_)&& platform) noexcept
        : platform_{std::move(platform)} {}

    auto initialize() -> void;
};

}  // namespace afengine::runtime

#endif
