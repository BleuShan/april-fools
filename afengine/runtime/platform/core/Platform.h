#ifndef AFENGINE_RUNTIME_PLATFORM_CORE_PLATFORM_H
#define AFENGINE_RUNTIME_PLATFORM_CORE_PLATFORM_H

#include <vector>

#include "afengine/foundation/memory/memory.h"
#include "afengine/foundation/types/types.h"
#include "afengine/macros/macros.h"

namespace afengine::runtime::platform::core {

class AFENGINE_EXPORT Platform {
  public:
    Platform(Platform& source) noexcept = default;
    Platform(Platform&& source) noexcept = default;
    virtual ~Platform() = default;

    auto operator=(const Platform& source) -> Platform& = default;
    auto operator=(Platform&& source) noexcept -> Platform& = default;

    inline auto Run() -> int {
      Initialize();
      return Main();
    }

    inline auto NotifyShutdown() -> void { Terminate(true); };

    inline auto Shutdown() -> void { Terminate(false); }

    [[nodiscard]] inline auto IsRunning() const -> bool { return isRunning_; }

    [[nodiscard]] inline auto CommandlineArguments() const
        -> std::vector<foundation::StringView> {
      return GetCommandLineArguments();
    }

  protected:
    Platform() = default;
    virtual auto Initialize() -> void = 0;
    virtual auto Main() -> int = 0;
    virtual auto Terminate(bool notify) -> void = 0;
    [[nodiscard]] virtual auto GetCommandLineArguments() const
        -> std::vector<foundation::StringView> = 0;

    inline auto IsRunning(bool value) -> bool {
      auto isRunning = isRunning_;
      if (value != isRunning_) {
        isRunning_ = value;
      }
      return isRunning;
    };

  private:
    bool isRunning_{false};
};

}  // namespace afengine::runtime::platform::core

#endif
