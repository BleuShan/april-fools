#ifndef AFENGINE_RUNTIME_PLATFORM_CORE_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_CORE_PLATFORM_H

#include <vector>

#include "afengine/foundation/memory/memory.h"
#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::core {
class AFENGINE_EXPORT Platform {
  public:
    enum class StatusTypes : uint8_t { BootstrapPending = 0, Stopped, Running };

    Platform(Platform& source) noexcept = default;
    Platform(Platform&& source) noexcept = default;
    virtual ~Platform() = default;

    auto operator=(const Platform& source) -> Platform& = default;
    auto operator=(Platform&& source) noexcept -> Platform& = default;

    auto Bootstrap() -> Platform& {
      if (status_ != StatusTypes::BootstrapPending) {
        throw std::domain_error("Invalid status");
      }

      PlatformBootstrap();
      status_ = StatusTypes::Stopped;
      return *this;
    }

    auto Run() -> int {
      if (status_ != StatusTypes::Stopped) {
        throw std::domain_error("Invalid status");
      }
      status_ = StatusTypes::Running;

      const auto result = PlatformRun();

      status_ = StatusTypes::Stopped;

      return result;
    }

    auto Shutdown() -> Platform& {
      if (status_ == StatusTypes::BootstrapPending) {
        throw std::domain_error("Invalid status");
      }

      PlatformShutdown();
      status_ = StatusTypes::BootstrapPending;
      return *this;
    }

    [[nodiscard]] auto Status() const { return status_; }

    [[nodiscard]] auto CommandlineArguments() const {
      return PlatformCommandlineArguments();
    }

  protected:
    Platform() = default;
    virtual auto PlatformBootstrap() -> void = 0;
    virtual auto PlatformRun() -> int = 0;
    virtual auto PlatformShutdown() -> void = 0;
    [[nodiscard]] virtual auto PlatformCommandlineArguments() const
        -> std::vector<foundation::StdStringView> = 0;

  private:
    StatusTypes status_{StatusTypes::BootstrapPending};
};

}  // namespace afengine::runtime::platform::core

#endif
