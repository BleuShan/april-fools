#ifndef AFENGINE_RUNTIME_PLATFORM_CORE_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_CORE_PLATFORM_H

#include <vector>

#include "ProcessInfo.h"
#include "afengine/foundation/memory/memory.h"
#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::core {

class AFENGINE_EXPORT Platform {
  public:
    enum class Status : uint8_t { BootstrapPending = 0, Stopped, Running };

    Platform(Platform& source) noexcept = default;
    Platform(Platform&& source) noexcept = default;
    virtual ~Platform() = default;

    auto operator=(const Platform& source) -> Platform& = default;
    auto operator=(Platform&& source) noexcept -> Platform& = default;

    auto initialize() -> Platform& {
      if (status_ != Status::BootstrapPending) {
        throw std::domain_error("Invalid status");
      }

      platformInitialize();
      status_ = Status::Stopped;
      return *this;
    }

    auto run() -> int {
      if (status_ != Status::Stopped) {
        throw std::domain_error("Invalid status");
      }
      status_ = Status::Running;

      const auto result = platformRun();

      status_ = Status::Stopped;

      return result;
    }

    auto shutdown() -> Platform& {
      if (status_ == Status::BootstrapPending) {
        throw std::domain_error("Invalid status");
      }

      platformShutdown();
      status_ = Status::BootstrapPending;
      return *this;
    }

    [[nodiscard]] auto currentStatus() const { return status_; }

    [[nodiscard]] auto processInfo() const { return platformProcessInfo(); }

  protected:
    Platform() = default;
    virtual auto platformInitialize() -> void = 0;
    virtual auto platformRun() -> int = 0;
    virtual auto platformShutdown() -> void = 0;
    [[nodiscard]] virtual auto platformProcessInfo() const
        -> core::ProcessInfo = 0;

  private:
    Status status_{Status::BootstrapPending};
};

}  // namespace afengine::runtime::platform::core

#endif
